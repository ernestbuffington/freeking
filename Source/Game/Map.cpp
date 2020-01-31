#include "Map.h"
#include "Lightmap.h"
#include "Texture2D.h"
#include "Shader.h"
#include "BspFile.h"
#include "BspFlags.h"
#include "DynamicModel.h"
#include "Paths.h"
#include "Profiler.h"
#include "ThirdParty/rectpack2d/finders_interface.h"
#include <array>

namespace Freeking
{
	Map* Map::Current = nullptr;

	void BrushMesh::Draw()
	{
		_vertexBinding->Bind();
		glDrawElements(GL_TRIANGLES, _vertexBinding->GetNumElements(), GL_UNSIGNED_INT, (void*)0);
		_vertexBinding->Unbind();
	}

	void BrushMesh::Commit()
	{
		if (Vertices.empty() || Indices.empty())
		{
			return;
		}

		static const int vertexSize = sizeof(Vertex);
		_vertexBuffer = std::make_unique<VertexBuffer>(Vertices.data(), Vertices.size(), vertexSize, GL_STATIC_DRAW);
		_indexBuffer = std::make_unique<IndexBuffer>(Indices.data(), Indices.size(), GL_UNSIGNED_INT);

		ArrayElement vertexLayout[] =
		{
			ArrayElement(_vertexBuffer.get(), 0, 3, ElementType::Float, vertexSize, 0),
			ArrayElement(_vertexBuffer.get(), 1, 3, ElementType::Float, vertexSize, 3 * sizeof(float)),
			ArrayElement(_vertexBuffer.get(), 2, 2, ElementType::Float, vertexSize, 6 * sizeof(float)),
			ArrayElement(_vertexBuffer.get(), 3, 2, ElementType::Float, vertexSize, 8 * sizeof(float)),
			ArrayElement(_vertexBuffer.get(), 4, 2, ElementType::Float, vertexSize, 10 * sizeof(float)),
		};

		_vertexBinding = std::make_unique<VertexBinding>();
		_vertexBinding->Create(vertexLayout, 5, *_indexBuffer, ElementType::UInt);
	}

	void BrushModel::RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material)
	{
		for (const auto& mesh : Meshes)
		{
			if (mesh.second->Translucent)
			{
				continue;
			}

			material->SetParameterValue("alphaCutOff", mesh.second->AlphaCutOff);
			material->SetParameterValue("diffuse", mesh.second->GetDiffuse().get());
			material->SetParameterValue("lightmap", mesh.second->GetLightmap().get());
			material->Apply();

			mesh.second->Draw();
		}
	}

	void BrushModel::RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material)
	{
		for (auto& mesh : Meshes)
		{
			if (!mesh.second->Translucent)
			{
				continue;
			}

			material->SetParameterValue("alphaMultiply", mesh.second->AlphaMultiply);
			material->SetParameterValue("diffuse", mesh.second->GetDiffuse().get());
			material->SetParameterValue("lightmap", mesh.second->GetLightmap().get());
			material->Apply();

			mesh.second->Draw();
		}
	}

	void Map::Tick(double dt)
	{
		for (const auto& entity : _entities)
		{
			entity->Tick(dt);
			entity->PostTick();
		}
	}

	void Map::Render(const Matrix4x4& viewProjection)
	{
		_material->SetParameterValue("viewProj", viewProjection);
		_material->SetParameterValue("diffuse", 0);
		_material->SetParameterValue("lightmap", 1);
		_material->SetParameterValue("brightness", 2.0f);

		glDisable(GL_BLEND);

		_material->SetParameterValue("alphaMultiply", 1.0f);

		for (const auto& entity : _worldEntities)
		{
			auto mvp = viewProjection * entity->GetTransform();
			_material->SetParameterValue("viewProj", mvp);
			entity->RenderOpaque(mvp, _material);
		}

		glEnable(GL_BLEND);

		_material->SetParameterValue("alphaCutOff", 0.0f);

		for (const auto& entity : _worldEntities)
		{
			auto mvp = viewProjection * entity->GetTransform();
			_material->SetParameterValue("viewProj", mvp);
			entity->RenderTranslucent(mvp, _material);
		}

		_material->Unbind();
	}

	Map::Map(const BspFile& bspFile)
	{
		Map::Current = this;

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
		_entityLump.Parse(entityString);
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
				_textures.emplace(textureName, Texture2D::Library.Get(path));
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
			const auto& model = models[modelIndex];
			auto brushModel = std::make_shared<BrushModel>();
			brushModel->BoundsMin = Vector3f(model.BoundsMin.x, model.BoundsMin.z, -model.BoundsMin.y);
			brushModel->BoundsMax = Vector3f(model.BoundsMax.x, model.BoundsMax.z, -model.BoundsMax.y);
			brushModel->Origin = Vector3f(model.Origin.x, model.Origin.z, -model.Origin.y);

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

				std::string textureName(faceTextureInfo.TextureName);
				auto masked = (faceTextureInfo.Flags & BspSurfaceFlags::Masked);
				auto trans = (faceTextureInfo.Flags & BspSurfaceFlags::Trans33) || (faceTextureInfo.Flags & BspSurfaceFlags::Trans66);

				auto [meshIt, meshInserted] = brushModel->Meshes.try_emplace(textureName, nullptr);
				auto mesh = meshInserted ? std::make_shared<BrushMesh>() : meshIt->second;
				if (meshInserted)
				{
					meshIt->second = mesh;
					mesh->SetDiffuse(_textures[textureName]);
					mesh->AlphaMultiply = trans ? ((faceTextureInfo.Flags & BspSurfaceFlags::Trans33) ? 0.33f : 0.66f) : 1.0f;
					mesh->AlphaCutOff = masked ? 0.67f : 0.0f;
					mesh->Translucent = trans;
				}

				const auto& faceTexture = _textures[textureName];
				auto textureWidth = faceTexture->GetWidth();
				auto textureHeight = faceTexture->GetHeight();

				float umin = std::numeric_limits<float>::max();
				float vmin = std::numeric_limits<float>::max();
				float umax = std::numeric_limits<float>::lowest();
				float vmax = std::numeric_limits<float>::lowest();

				int baseVertex = static_cast<int>(mesh->GetNumVertices());

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

		_material = std::make_shared<Material>(Shader::Library.Get("Shaders/Lightmapped.shader"));

		pf.Start();

		for (const auto& e : _entityLump.Entities)
		{
			const auto& classname = e.classname;
			if (classname.empty())
			{
				continue;
			}

			if (auto newEntity = IEntity::Make(classname))
			{
				newEntity->InitializeProperties(e);
				newEntity->Initialize();
				newEntity->PostInitialize();
				newEntity->Spawn();

				_entities.push_back(newEntity);

				if (auto worldEntity = std::dynamic_pointer_cast<BaseWorldEntity>(newEntity))
				{
					_worldEntities.push_back(worldEntity);
				}
			}
		}

		pf.Stop("Create entities");
	}
}
