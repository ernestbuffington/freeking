#include "Map.h"
#include "Lightmap.h"
#include "Texture2D.h"
#include "BspFile.h"
#include "BspFlags.h"
#include "Util.h"
#include "Mesh.h"
#include "Paths.h"
#include "Profiler.h"
#include <array>
#include "ThirdParty/rectpack2d/finders_interface.h"

namespace Freeking
{
	void BrushModelEntity::Initialize()
	{
		if (_modelIndex < 0)
		{
			return;
		}

		_model = _map->GetBrushModel(_modelIndex);
	}

	void BrushModelEntity::RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader)
	{
		if (_model)
		{
			_model->RenderOpaque(viewProjection, shader);
		}
	}

	void BrushModelEntity::RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader)
	{
		if (_model)
		{
			_model->RenderTranslucent(viewProjection, shader);
		}
	}

	void DoorEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		_time += (dt * Math::DegreesToRadians(_speed));
		_time = std::fmodf(_time, Math::TWO_PI);

		float t = (std::sinf(_time) + 1.0f) * 0.5f;
		float distance = (_model->BoundsMax - _model->BoundsMin).y - 8.0f;

		_position = _initialPosition + Vector3f(0, distance * (t * 1.0f), 0);
	}

	void BrushModel::RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader)
	{
		for (const auto& mesh : Meshes)
		{
			if (mesh.second->Translucent)
			{
				continue;
			}

			shader->SetUniformValue("alphaCutOff", mesh.second->AlphaCutOff);
			mesh.second->Draw();
		}
	}

	void BrushModel::RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader)
	{
		for (auto& mesh : Meshes)
		{
			if (!mesh.second->Translucent)
			{
				continue;
			}

			shader->SetUniformValue("alphaMultiply", mesh.second->AlphaMultiply);
			mesh.second->Draw();
		}
	}

	void Map::Tick(double dt)
	{
		for (const auto& entity : _entities)
		{
			entity->Tick(dt);
		}
	}

	void Map::Render(const Matrix4x4& viewProjection)
	{
		_shader->Bind();
		_shader->SetUniformValue("viewProj", viewProjection);
		_shader->SetUniformValue("diffuse", 0);
		_shader->SetUniformValue("lightmap", 1);
		_shader->SetUniformValue("brightness", 2.0f);

		_textureSampler->Bind(0);
		_lightmapSampler->Bind(1);

		glDisable(GL_BLEND);

		_shader->SetUniformValue("alphaMultiply", 1.0f);

		for (const auto& entity : _entities)
		{
			auto mvp = viewProjection * entity->GetTransform();
			_shader->SetUniformValue("viewProj", mvp);
			entity->RenderOpaque(mvp, _shader);
		}

		glEnable(GL_BLEND);

		_shader->SetUniformValue("alphaCutOff", 0.0f);

		for (const auto& entity : _entities)
		{
			auto mvp = viewProjection * entity->GetTransform();
			_shader->SetUniformValue("viewProj", mvp);
			entity->RenderTranslucent(mvp, _shader);
		}

		_shader->Unbind();
	}

	Map::Map(const BspFile& bspFile)
	{
		Profiler pf;

		auto entities = bspFile.GetLumpArray<char>(bspFile.Header.Entities);
		auto vertices = bspFile.GetLumpArray<Vector3f>(bspFile.Header.Vertices);
		auto models = bspFile.GetLumpArray<BspModel>(bspFile.Header.Models);
		auto faces = bspFile.GetLumpArray<BspFace>(bspFile.Header.Faces);
		auto edges = bspFile.GetLumpArray<BspEdge>(bspFile.Header.Edges);
		auto faceEdges = bspFile.GetLumpArray<int32_t>(bspFile.Header.FaceEdges);
		auto planes = bspFile.GetLumpArray<BspPlane>(bspFile.Header.Planes);
		auto textureInfo = bspFile.GetLumpArray<BspTextureInfo>(bspFile.Header.TextureInfo);
		auto lightmapData = bspFile.GetLumpArray<uint8_t>(bspFile.Header.Lightmaps);

		pf.Start();
		std::string entityString(entities.Data(), entities.Num());
		_entityLump = std::make_unique<EntityLump>(entityString);
		pf.Stop("EntityLump");

		pf.Start();
		std::map<std::string, std::shared_ptr<Texture2D>> textures;
		for (int i = 0; i < textureInfo.Num(); ++i)
		{
			const auto& texInfo = textureInfo[i];
			auto textureName = std::string(texInfo.TextureName);

			if (_textures.find(textureName) == _textures.end())
			{
				auto path = "textures/" + (textureName + std::string(".tga"));
				_textures.emplace(textureName, Util::LoadTexture(path));
			}
		}
		std::cout << _textures.size() << " map textures" << std::endl;

		pf.Stop("Map textures");

		pf.Start();

		int lmSize = 2048;
		auto lightmapImage = std::make_shared<LightmapImage>(lmSize, lmSize);

		std::array<uint8_t, (16 * 16) * 3> blackPixels = { 0 };
		lightmapImage->Insert(0, 0, 16, 16, blackPixels.data());
		Vector2f firstLightmapUV(8.0f / lightmapImage->GetWidth(), 8.0f / lightmapImage->GetHeight());

		auto packingRoot = rectpack2D::empty_spaces<false>({ lmSize, lmSize });
		packingRoot.insert({ 16, 16 });

		for (int modelIndex = 0; modelIndex < models.Num(); ++modelIndex)
		{
			if (modelIndex > 0)
			{
				//break;
			}

			const auto& model = models[modelIndex];
			auto brushModel = std::make_shared<BrushModel>();
			brushModel->BoundsMin = model.BoundsMin;
			brushModel->BoundsMax = model.BoundsMax;
			brushModel->Origin = model.Origin;

			for (int faceIndex = model.FirstFace; faceIndex < (model.FirstFace + model.NumFaces); ++faceIndex)
			{
				const auto& face = faces[faceIndex];
				const auto& faceTextureInfo = textureInfo[face.TextureInfo];

				if ((faceTextureInfo.Flags & BspSurfaceFlags::NoDraw) ||
					(faceTextureInfo.Flags & BspSurfaceFlags::Sky) ||
					(faceTextureInfo.Flags & BspSurfaceFlags::Warp))
				{
					continue;
				}

				auto masked = (faceTextureInfo.Flags & BspSurfaceFlags::Masked);
				auto trans = (faceTextureInfo.Flags & BspSurfaceFlags::Trans33) || (faceTextureInfo.Flags & BspSurfaceFlags::Trans66);

				BrushMesh* mesh = nullptr;
				auto textureName = std::string(faceTextureInfo.TextureName);

				if (brushModel->Meshes.find(textureName) == brushModel->Meshes.end())
				{
					auto newMesh = std::make_shared<BrushMesh>();
					newMesh->SetDiffuse(_textures[textureName]);
					newMesh->AlphaMultiply = trans ? ((faceTextureInfo.Flags & BspSurfaceFlags::Trans33) ? 0.33f : 0.66f) : 1.0f;
					newMesh->AlphaCutOff = masked ? 0.67f : 0.0f;
					newMesh->Translucent = trans;
					brushModel->Meshes.emplace(textureName, std::move(newMesh));
				}

				mesh = brushModel->Meshes[textureName].get();

				if (mesh == nullptr)
				{
					continue;
				}

				const auto& faceTexture = _textures[textureName];
				auto textureWidth = faceTexture->GetWidth();
				auto textureHeight = faceTexture->GetHeight();

				float umin = std::numeric_limits<float>::max();
				float vmin = std::numeric_limits<float>::max();
				float umax = std::numeric_limits<float>::lowest();
				float vmax = std::numeric_limits<float>::lowest();

				int baseVertex = mesh->GetNumVertices();

				std::vector<BrushMesh::Vertex> faceVertices;
				faceVertices.resize(face.NumEdges);

				std::vector<Vector2f> faceUVs;
				faceUVs.resize(face.NumEdges);

				for (int edgeIndex = 0; edgeIndex < face.NumEdges; ++edgeIndex)
				{
					const auto& faceEdge = faceEdges[face.FirstEdge + edgeIndex];
					const auto& v0 = vertices[faceEdge < 0 ? edges[-faceEdge].A : edges[faceEdge].B];
					Vector3f position(v0.x, v0.z, -v0.y);

					const auto& plane = planes[face.Plane];
					Vector3f normal = (face.PlaneSide == 0) ? plane.Normal : plane.Normal * -1.0f;

					float u = v0.x * faceTextureInfo.AxisU.x + v0.y * faceTextureInfo.AxisU.y + v0.z * faceTextureInfo.AxisU.z + faceTextureInfo.OffsetU;
					float v = v0.x * faceTextureInfo.AxisV.x + v0.y * faceTextureInfo.AxisV.y + v0.z * faceTextureInfo.AxisV.z + faceTextureInfo.OffsetV;

					umin = Math::Min(u, umin);
					vmin = Math::Min(v, vmin);
					umax = Math::Max(u, umax);
					vmax = Math::Max(v, vmax);

					faceUVs[edgeIndex] = Vector2f(u, v);

					u /= (float)textureWidth;
					v /= (float)textureHeight;

					faceVertices[edgeIndex] = { position, normal, { Vector2f(u, v), firstLightmapUV, firstLightmapUV } };
				}

				if (face.LightmapOffset != 0)
				{
					float lminu = floor(umin / 16.0f);
					float lmaxu = ceil(umax / 16.0f);
					float lminv = floor(vmin / 16.0f);
					float lmaxv = ceil(vmax / 16.0f);

					int lwidth = (int)(lmaxu - lminu + 1);
					int lheight = (int)(lmaxv - lminv + 1);

					for (int lightStyleIndex = 0; lightStyleIndex < 4; ++lightStyleIndex)
					{
						auto lightStyle = face.LightmapStyles[lightStyleIndex];
						if (lightStyle == 255)
						{
							continue;
						}

						auto packingNode = packingRoot.insert({ lwidth, lheight });

						if (packingNode.has_value())
						{
							auto lightmapOffset = face.LightmapOffset + (((lwidth * lheight) * 3) * lightStyleIndex);
							lightmapImage->Insert(packingNode->x, packingNode->y, lwidth, lheight, lightmapData.Data() + lightmapOffset);

							auto uvIndex = lightStyleIndex + 1;

							for (size_t i = 0; i < faceVertices.size(); ++i)
							{
								auto& vertex = faceVertices[i];
								auto& faceUV = faceUVs[i];

								float ucoord = faceUV.x;
								ucoord -= floor(umin / 16.0f) * 16.0f;
								ucoord += 8.0f;
								ucoord /= lwidth * 16.0f;

								float vcoord = faceUV.y;
								vcoord -= floor(vmin / 16.0f) * 16.0f;
								vcoord += 8.0f;
								vcoord /= lheight * 16.0f;

								ucoord = ((ucoord * lwidth) + packingNode->x) / lightmapImage->GetWidth();
								vcoord = ((vcoord * lheight) + packingNode->y) / lightmapImage->GetHeight();

								vertex.UV[uvIndex].x = ucoord;
								vertex.UV[uvIndex].y = vcoord;
							}
						}
					}
				}

				for (size_t i = 0; i < faceVertices.size(); ++i)
				{
					mesh->Vertices.emplace_back(faceVertices[i]);
				}

				int numTriangles = face.NumEdges - 2;

				for (int triangleIndex = 0; triangleIndex < numTriangles; ++triangleIndex)
				{
					uint32_t baseIndex = baseVertex + triangleIndex;
					mesh->Indices.emplace_back(baseIndex + 2);
					mesh->Indices.emplace_back(baseIndex + 1);
					mesh->Indices.emplace_back(baseVertex);
				}
			}

			_models.push_back(std::move(brushModel));
		}
		pf.Stop("Map create");

		pf.Start();
		_lightmapTexture = std::make_shared<Texture2D>(
			lmSize,
			lmSize,
			GL_RGBA,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			lightmapImage->Data.data());
		pf.Stop("Lightmap upload");

		pf.Start();

		for (auto& model : _models)
		{
			for (auto& mesh : model->Meshes)
			{
				mesh.second->SetLightmap(_lightmapTexture);
				mesh.second->Commit();
			}
		}

		pf.Stop("Map commit");

		_shader = Util::LoadShader("Shaders/Mesh.vert", "Shaders/Mesh.frag");
		_textureSampler = std::make_shared<TextureSampler>(WrapMode::WRAPMODE_REPEAT, FilterMode::FILTERMODE_LINEAR);
		_lightmapSampler = std::make_shared<TextureSampler>(WrapMode::WRAPMODE_CLAMP_EDGE, FilterMode::FILTERMODE_LINEAR_NO_MIP);
		
		pf.Start();

		for (const auto& e : _entityLump->Entities)
		{
			const auto& classname = e.classname;
			std::shared_ptr<BaseEntity> newEntity;

			if (classname == "worldspawn")
			{
				newEntity = std::make_shared<WorldSpawnEntity>(this);
			}
			else if (classname == "func_rotating")
			{
				newEntity = std::make_shared<RotatingEntity>(this);
			}
			else if (classname == "func_button" ||
					 classname == "func_explosive" ||
					 classname == "func_wall")
			{
				newEntity = std::make_shared<BrushModelEntity>(this);
			}
			else if (classname == "func_door")
			{
				newEntity = std::make_shared<DoorEntity>(this);
			}
			else if (classname == "func_door_rotating")
			{
				newEntity = std::make_shared<DoorRotatingEntity>(this);
			}

			if (newEntity)
			{
				if (!e.logic)
				{
					Vector3f origin(e.origin.x, e.origin.z, -e.origin.y);
					Quaternion rotation = Quaternion(0, 0, 0, 1);

					if (e.angle > 0)
					{
						rotation = Quaternion::FromDegreeAngles(Vector3f(0, e.angle, 0));
					}

					newEntity->SetPosition(origin);
					newEntity->SetRotation(rotation);
				}

				for (const auto& keyValue : e.keyValues)
				{
					newEntity->SetProperty({ keyValue.first, keyValue.second });
				}

				newEntity->Initialize();
				_entities.push_back(std::move(newEntity));
			}
		}

		pf.Stop("Create entities");
	}
}
