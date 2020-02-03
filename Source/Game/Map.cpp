#include "Map.h"
#include "Lightmap.h"
#include "Texture2D.h"
#include "Shader.h"
#include "BspFile.h"
#include "BspFlags.h"
#include "DynamicModel.h"
#include "Paths.h"
#include "Profiler.h"
#include "LineRenderer.h"
#include "ThirdParty/rectpack2d/finders_interface.h"
#include <array>

namespace Freeking
{
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

	const static std::array<std::string, 21> lightSequences
	{
		"m",
		"mmnmmommommnonmmonqnmmo",
		"abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba",
		"mmmmmaaaaammmmmaaaaaabcdefgabcdefg",
		"mamamamamama",
		"jklmnopqrstuvwxyzyxwvutsrqponmlkj",
		"nmonqnmomnmomomno",
		"mmmaaaabcdefgmmmmaaaammmaamm",
		"mmmaaammmaaammmabcdefaaaammmmabcdefmmmaaaa",
		"aaaaaaaazzzzzzzz",
		"mmamammmmammamamaaamammma",
		"abcdefghijklmnopqrrqponmlkjihgfedcba",
		"mmnommomhkmmomnonmmonqnmmo",
		"kmamaamakmmmaakmamakmakmmmma",
		"kmmmakakmmaaamammamkmamakmmmma",
		"mmnnoonnmmmmmmmmmnmmmmnonmmmmmmm",
		"mmmmnonmmmmnmmmmmnonmmmmmnmmmmmmm",
		"zzzzzzzzaaaaaaaa",
		"zzzzzzzzaaaaaaaaaaaaaaaa",
		"aaaaaaaazzzzzzzzaaaaaaaa",
		"aaaaaaaaaaaaaaaazzzzzzzz"
	};

	class LightStyle
	{
	public:

		LightStyle(const std::string_view& values, double speed, bool interpolated) :
			_speed(speed),
			_lastSample(0.0f),
			_interpolated(interpolated),
			_disabled(false)
		{
			_samples.resize(values.size());

			for (auto i = 0; i < _samples.size(); ++i)
			{
				_samples[i] = ((float)(values[i] - 97) / 25.0f) * 2.0f;
			}
		}

		void SetEnabled(bool enabled)
		{
			_disabled = !enabled;
		}

		void Update(double time)
		{
			if (_disabled)
			{
				_lastSample = 0.0f;

				return;
			}

			if (_speed < 0.0)
			{
				return;
			}

			size_t numSamples = _samples.size();
			if (numSamples == 1)
			{
				_lastSample = _samples.at(0);

				return;
			}

			time = fmod(time, static_cast<double>(numSamples) * (1.0 / _speed)) * _speed;
			size_t index = static_cast<size_t>(floor(time));
			double fraction = time - static_cast<double>(index);
			index %= numSamples;

			if (_interpolated)
			{
				size_t nextIndex = (index + 1) % numSamples;

				float a = _samples.at(index);
				float b = _samples.at(nextIndex);

				if (index == nextIndex)
				{
					_lastSample = _samples.at(index);
				}
				else
				{
					_lastSample = (a + static_cast<float>(fraction) * (b - a));
				}
			}
			else
			{
				_lastSample = _samples.at(index);
			}
		}

		inline float GetSample() const { return _lastSample; }

	private:

		std::vector<float> _samples;
		double _speed;
		float _lastSample;
		bool _interpolated;
		bool _disabled;
	};

	class LightStyles
	{
	public:

		void Update(double time)
		{
			for (auto& style : _styles)
			{
				style.Update(time);
			}
		}

		void SetEnabled(size_t index, bool enabled)
		{
			if (index < _styles.size())
			{
				_styles.at(index).SetEnabled(enabled);
			}
		}

		void Add(const std::string_view& values, double speed, bool interpolated)
		{
			_styles.emplace_back(values, speed, interpolated);
		}

		float GetSample(size_t index) const
		{
			if (index < _styles.size())
			{
				return _styles.at(index).GetSample();
			}

			return 0.0f;
		}

	private:

		std::vector<LightStyle> _styles;
	};

	void BrushModel::RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material)
	{
		for (const auto& mesh : Meshes)
		{
			if (mesh.second->Translucent)
			{
				continue;
			}

			float brightness = Map::LightStyles.GetSample(mesh.second->LightStyles[1]);
			material->SetParameterValue("brightness", brightness * 2.0f);
			material->SetParameterValue("alphaCutOff", mesh.second->AlphaCutOff);
			material->SetParameterValue("diffuse", mesh.second->GetDiffuse().get());
			material->SetParameterValue("lightmap", mesh.second->GetLightmap().get());
			material->Apply();

			mesh.second->Draw();
		}
	}

	void BrushModel::RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material, bool forceTranslucent)
	{
		for (auto& mesh : Meshes)
		{
			if (!mesh.second->Translucent && !forceTranslucent)
			{
				continue;
			}

			float brightness = Map::LightStyles.GetSample(mesh.second->LightStyles[1]);
			material->SetParameterValue("brightness", brightness * 2.0f);
			material->SetParameterValue("alphaMultiply", mesh.second->AlphaMultiply);
			material->SetParameterValue("diffuse", mesh.second->GetDiffuse().get());
			material->SetParameterValue("lightmap", mesh.second->GetLightmap().get());
			material->Apply();

			mesh.second->Draw();
		}
	}

	void Map::Tick(double dt)
	{
		Time += dt;
		LightStyles.Update(Time);

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
		_material->SetParameterValue("brightness", 0.0f);

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

	Map* Map::Current = nullptr;
	double Map::Time = 0.0;
	LightStyles Map::LightStyles;

	Map::Map(const BspFile& bspFile)
	{
		Map::Current = this;

		for (const auto& l : lightSequences)
		{
			LightStyles.Add(l, 10.0, true);
		}

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
		if (!EntityLump::Parse(entityString, _entityKeyValues))
		{
			std::cout << "Error parsing entity lump" << std::endl;
		}

		pf.Stop("EntityLump");

		pf.Start();

		std::map<std::string, uint32_t> textureIds;

		for (int i = 0; i < textureInfo.Num(); ++i)
		{
			const auto& texInfo = textureInfo[i];
			auto textureName = std::string(texInfo.TextureName);

			if (textureIds.find(textureName) == textureIds.end())
			{
				auto path = "textures/" + (textureName + std::string(".tga"));
				textureIds.emplace(textureName, static_cast<uint32_t>(_textures.size()));
				_textures.push_back(Texture2D::Library.Get(path));
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
			Vector3f boundsMin(model.BoundsMin.x, model.BoundsMin.z, -model.BoundsMin.y);
			Vector3f boundsMax(model.BoundsMax.x, model.BoundsMax.z, -model.BoundsMax.y);
			brushModel->BoundsMin = Vector3f(Math::Min(boundsMin.x, boundsMax.x), Math::Min(boundsMin.y, boundsMax.y), Math::Min(boundsMin.z, boundsMax.z));
			brushModel->BoundsMax = Vector3f(Math::Max(boundsMin.x, boundsMax.x), Math::Max(boundsMin.y, boundsMax.y), Math::Max(boundsMin.z, boundsMax.z));
			brushModel->Origin = Vector3f(model.Origin.x, model.Origin.z, -model.Origin.y);

			for (int faceIndex = model.FirstFace; faceIndex < (model.FirstFace + model.NumFaces); ++faceIndex)
			{
				const auto& face = faces[faceIndex];
				const auto& faceTextureInfo = textureInfo[face.TextureInfo];

				if ((faceTextureInfo.Flags[BspSurfaceFlags::NoDraw]) ||
					(faceTextureInfo.Flags[BspSurfaceFlags::Sky]) ||
					(faceTextureInfo.Flags[BspSurfaceFlags::Warp]))
				{
					continue;
				}

				std::string textureName(faceTextureInfo.TextureName);
				auto masked = (faceTextureInfo.Flags[BspSurfaceFlags::Masked]);
				auto trans = (faceTextureInfo.Flags[BspSurfaceFlags::Trans33]) || (faceTextureInfo.Flags[BspSurfaceFlags::Trans66]);
				auto textureId = textureIds[textureName];
				auto texture = _textures.at(textureId);

				uint32_t lightStyleKey =
					face.LightmapStyles[0] << 24 |
					face.LightmapStyles[1] << 16 |
					face.LightmapStyles[2] << 8 |
					face.LightmapStyles[3];

				auto meshKey = BrushModel::MeshKey(textureId, lightStyleKey);
				auto [meshIt, meshInserted] = brushModel->Meshes.try_emplace(meshKey, nullptr);
				auto mesh = meshInserted ? std::make_shared<BrushMesh>() : meshIt->second;
				if (meshInserted)
				{
					meshIt->second = mesh;
					mesh->LightStyles[0] = face.LightmapStyles[0];
					mesh->LightStyles[1] = face.LightmapStyles[1];
					mesh->LightStyles[2] = face.LightmapStyles[2];
					mesh->LightStyles[3] = face.LightmapStyles[3];
					mesh->SetDiffuse(texture);
					mesh->AlphaMultiply = trans ? ((faceTextureInfo.Flags[BspSurfaceFlags::Trans33]) ? 0.33f : 0.66f) : 1.0f;
					mesh->AlphaCutOff = masked ? 0.67f : 0.0f;
					mesh->Translucent = trans;
				}

				auto textureWidth = texture->GetWidth();
				auto textureHeight = texture->GetHeight();

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
			GL_RGBA8,
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

		for (const auto& e : _entityKeyValues)
		{
			std::string classname = e.GetClassnameProperty();
			if (classname.empty())
			{
				continue;
			}

			if (auto newEntity = BaseEntity::Make(classname))
			{
				newEntity->InitializeProperties(e);
				newEntity->Initialize();
				newEntity->PostInitialize();
				newEntity->Spawn();

				_entities.push_back(newEntity);

				if (auto worldEntity = std::dynamic_pointer_cast<PrimitiveEntity>(newEntity))
				{
					_worldEntities.push_back(worldEntity);
				}
			}
		}

		pf.Stop("Create entities");
	}
}
