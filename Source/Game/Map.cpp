#include "Map.h"
#include "Lightmap.h"
#include "Texture2D.h"
#include "Shader.h"
#include "BspFlags.h"
#include "DynamicModel.h"
#include "Paths.h"
#include "Profiler.h"
#include "LineRenderer.h"
#include "Util.h"
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

			time = fmod(time, static_cast<double>(numSamples)* (1.0 / _speed))* _speed;
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
					_lastSample = (a + static_cast<float>(fraction)* (b - a));
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

	void BrushModel::RenderOpaque(Shader* shader)
	{
		if (!shader)
		{
			return;
		}

		for (const auto& mesh : Meshes)
		{
			if (mesh.second->Translucent)
			{
				continue;
			}

			float brightness = Map::LightStyles.GetSample(mesh.second->LightStyles[1]);
			shader->SetParameterValue("brightness", brightness * 2.0f);
			shader->SetParameterValue("alphaCutOff", mesh.second->AlphaCutOff);
			shader->SetParameterValue("diffuse", mesh.second->GetDiffuse().get());
			shader->SetParameterValue("lightmap", mesh.second->GetLightmap().get());

			mesh.second->Draw();
		}
	}

	void BrushModel::RenderTranslucent(Shader* shader, bool forceTranslucent)
	{
		if (!shader)
		{
			return;
		}

		for (auto& mesh : Meshes)
		{
			if (!mesh.second->Translucent && !forceTranslucent)
			{
				continue;
			}

			float brightness = Map::LightStyles.GetSample(mesh.second->LightStyles[1]);
			shader->SetParameterValue("brightness", brightness * 2.0f);
			shader->SetParameterValue("alphaMultiply", mesh.second->AlphaMultiply);
			shader->SetParameterValue("diffuse", mesh.second->GetDiffuse().get());
			shader->SetParameterValue("lightmap", mesh.second->GetLightmap().get());

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

	void Map::Render()
	{
		glDisable(GL_BLEND);

		for (const auto& entity : _worldEntities)
		{
			if (entity->IsHidden())
			{
				continue;
			}

			entity->PreRender(false);
			entity->RenderOpaque();
		}

		glEnable(GL_BLEND);

		for (const auto& entity : _worldEntities)
		{
			if (entity->IsHidden())
			{
				continue;
			}

			entity->PreRender(true);
			entity->RenderTranslucent();
		}
	}

	Map* Map::Current = nullptr;
	double Map::Time = 0.0;
	LightStyles Map::LightStyles;

	float Map::GetLightStyleSample(size_t index)
	{
		return LightStyles.GetSample(index);
	}

	Map::Map(const std::string& mapName)
	{
		Map::Current = this;

		for (const auto& l : lightSequences)
		{
			LightStyles.Add(l, 10.0, true);
		}

		Profiler pf;

		_fileData = std::move(FileSystem::GetFileData("maps/" + mapName + ".bsp"));
		const BspFile& bspFile = BspFile::Create(_fileData.data());

		auto entities = bspFile.GetLumpArray<char>(bspFile.Header.Entities);
		auto vertices = bspFile.GetLumpArray<Vector3f>(bspFile.Header.Vertices);
		_brushModels = bspFile.GetLumpArray<BspModel>(bspFile.Header.Models);
		auto faces = bspFile.GetLumpArray<BspFace>(bspFile.Header.Faces);
		auto edges = bspFile.GetLumpArray<BspEdge>(bspFile.Header.Edges);
		auto faceEdges = bspFile.GetLumpArray<int32_t>(bspFile.Header.FaceEdges);
		auto planes = bspFile.GetLumpArray<BspPlane>(bspFile.Header.Planes);
		auto lightmapData = bspFile.GetLumpArray<uint8_t>(bspFile.Header.Lightmaps);
		_textureInfo = bspFile.GetLumpArray<BspTextureInfo>(bspFile.Header.TextureInfo);
		_brushes = bspFile.GetLumpArray<BspBrush>(bspFile.Header.Brushes);
		_brushSides = bspFile.GetLumpArray<BspBrushSide>(bspFile.Header.BrushSides);
		_planes = bspFile.GetLumpArray<BspPlane>(bspFile.Header.Planes);
		_nodes = bspFile.GetLumpArray<BspNode>(bspFile.Header.Nodes);
		_leafs = bspFile.GetLumpArray<BspLeaf>(bspFile.Header.Leafs);
		_leafBrushes = bspFile.GetLumpArray<int16_t>(bspFile.Header.LeafBrushes);

		pf.Start();

		std::string entityString(entities.Data(), entities.Num());
		if (!EntityLump::Parse(entityString, _entityKeyValues))
		{
			std::cout << "Error parsing entity lump" << std::endl;
		}

		pf.Stop("EntityLump");

		pf.Start();

		std::unordered_map<std::string, uint32_t> textureIds;

		for (int i = 0; i < _textureInfo.Num(); ++i)
		{
			const auto& texInfo = _textureInfo[i];
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

		int lmSize = 4096;
		auto lightmapImage = std::make_shared<LightmapImage>(lmSize, lmSize);
		auto packingRoot = rectpack2D::empty_spaces<false>({ lmSize, lmSize });

		for (int modelIndex = 0; modelIndex < _brushModels.Num(); ++modelIndex)
		{
			const auto& model = _brushModels[modelIndex];
			auto brushModel = std::make_shared<BrushModel>();
			Vector3f boundsMin(model.BoundsMin.x, model.BoundsMin.z, -model.BoundsMin.y);
			Vector3f boundsMax(model.BoundsMax.x, model.BoundsMax.z, -model.BoundsMax.y);
			brushModel->BoundsMin = Vector3f(Math::Min(boundsMin.x, boundsMax.x), Math::Min(boundsMin.y, boundsMax.y), Math::Min(boundsMin.z, boundsMax.z));
			brushModel->BoundsMax = Vector3f(Math::Max(boundsMin.x, boundsMax.x), Math::Max(boundsMin.y, boundsMax.y), Math::Max(boundsMin.z, boundsMax.z));
			brushModel->Origin = Vector3f(model.Origin.x, model.Origin.z, -model.Origin.y);

			for (int faceIndex = model.FirstFace; faceIndex < (model.FirstFace + model.NumFaces); ++faceIndex)
			{
				const auto& face = faces[faceIndex];
				const auto& faceTextureInfo = _textureInfo[face.TextureInfo];

				if ((faceTextureInfo.Flags[BspSurfaceFlags::NoDraw]) ||
					(faceTextureInfo.Flags[BspSurfaceFlags::Sky]) ||
					(faceTextureInfo.Flags[BspSurfaceFlags::Warp]))
				{
					continue;
				}

				if (face.LightmapOffset < 0)
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

					faceVertices[edgeIndex] = { position, normal, { Vector2f(u, v), 0, 0 } };
				}

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

		pf.Start();

		for (const auto& entityProperties : _entityKeyValues)
		{
			std::string classname = entityProperties.GetClassnameProperty();
			if (classname.empty())
			{
				continue;
			}

			if (auto newEntity = BaseEntity::Make(classname))
			{
				if (const auto& targetname = entityProperties.GetTargetnameProperty())
				{
					_targetEntities[targetname].push_back(newEntity);
				}

				newEntity->InitializeProperties(entityProperties);
				newEntity->Initialize();
				newEntity->PostInitialize();
				newEntity->Spawn();

				_entities.push_back(newEntity);

				if (auto worldEntity = std::dynamic_pointer_cast<PrimitiveEntity>(newEntity))
				{
					_worldEntities.push_back(worldEntity);
				}
			}
			else
			{
				std::cout << "Could not make entity \"" << classname << "\"" << std::endl;
			}
		}

		pf.Stop("Create entities");
	}

	std::vector<std::shared_ptr<BaseEntity>> Map::GetTargetEntities(const std::string& targetName)
	{
		if (auto it = _targetEntities.find(targetName); it != _targetEntities.end())
		{
			return it->second;
		}

		return {};
	}

	void Map::RecursiveHullCheck(int num, float p1f, float p2f, const Vector3f& mins, const Vector3f& maxs, const Vector3f& p1, const Vector3f& p2, TraceResult& trace, bool isPoint, const Vector3f& extents, const BspContentFlags& contents)
	{
		if (trace.fraction <= p1f)
		{
			return;
		}

		if (num < 0)
		{
			TraceToLeaf(mins, maxs, trace, isPoint, -1 - num, contents);

			return;
		}

		float t1, t2, offset;

		const BspNode& node = _nodes[num];
		const BspPlane& plane = _planes[node.PlaneNum];

		if (plane.Type < 3)
		{
			t1 = p1[plane.Type] - plane.Distance;
			t2 = p2[plane.Type] - plane.Distance;
			offset = extents[plane.Type];
		}
		else
		{
			t1 = Vector3f::Dot(plane.Normal, p1) - plane.Distance;
			t2 = Vector3f::Dot(plane.Normal, p2) - plane.Distance;

			if (isPoint)
			{
				offset = 0;
			}
			else
			{
				offset =
					fabs(extents[0] * plane.Normal[0]) +
					fabs(extents[1] * plane.Normal[1]) +
					fabs(extents[2] * plane.Normal[2]);
			}
		}

		if (t1 >= offset && t2 >= offset)
		{
			RecursiveHullCheck(node.Children[0], p1f, p2f, mins, maxs, p1, p2, trace, isPoint, extents, contents);

			return;
		}
		if (t1 < -offset && t2 < -offset)
		{
			RecursiveHullCheck(node.Children[1], p1f, p2f, mins, maxs, p1, p2, trace, isPoint, extents, contents);

			return;
		}

		int side;
		float idist;
		float frac;
		float frac2;

		if (t1 < t2)
		{
			idist = 1.0f / (t1 - t2);
			side = 1;
			frac2 = (t1 + offset + 0.03125f) * idist;
			frac = (t1 - offset + 0.03125f) * idist;
		}
		else if (t1 > t2)
		{
			idist = 1.0f / (t1 - t2);
			side = 0;
			frac2 = (t1 - offset - 0.03125f) * idist;
			frac = (t1 + offset + 0.03125f) * idist;
		}
		else
		{
			side = 0;
			frac = 1.0f;
			frac2 = 0.0f;
		}

		if (frac < 0.0f)
		{
			frac = 0.0f;
		}

		if (frac > 1.0f)
		{
			frac = 1.0f;
		}

		float midf = p1f + (p2f - p1f) * frac;
		Vector3f mid;

		for (int i = 0; i < 3; i++)
		{
			mid[i] = p1[i] + frac * (p2[i] - p1[i]);
		}

		RecursiveHullCheck(node.Children[side], p1f, midf, mins, maxs, p1, mid, trace, isPoint, extents, contents);

		if (frac2 < 0.0f)
		{
			frac2 = 0.0f;
		}

		if (frac2 > 1.0f)
		{
			frac2 = 1.0f;
		}

		midf = p1f + (p2f - p1f) * frac2;

		for (int i = 0; i < 3; i++)
		{
			mid[i] = p1[i] + frac2 * (p2[i] - p1[i]);
		}

		RecursiveHullCheck(node.Children[side ^ 1], midf, p2f, mins, maxs, mid, p2, trace, isPoint, extents, contents);
	}

	void Map::TraceToLeaf(const Vector3f& mins, const Vector3f& maxs, TraceResult& trace, bool isPoint, int leafIndex, const BspContentFlags& contents)
	{
		const BspLeaf& leaf = _leafs[leafIndex];

		if (!leaf.Contents[contents])
		{
			return;
		}

		for (int k = 0; k < leaf.NumLeafBrushes; k++)
		{
			const BspBrush& brush = _brushes[_leafBrushes[leaf.FirstLeafBrush + k]];

			if (!brush.Contents[contents])
			{
				continue;
			}

			ClipBoxToBrush(trace.startPosition, trace.endPosition, mins, maxs, trace, brush, isPoint);

			if (!trace.fraction)
			{
				return;
			}
		}
	}

	void Map::ClipBoxToBrush(const Vector3f& start, const Vector3f& end, const Vector3f& mins, const Vector3f& maxs, TraceResult& trace, const BspBrush& brush, bool isPoint)
	{
		if (brush.NumSides == 0)
		{
			return;
		}

		float enterFrac = -1.0;
		float leaveFrac = 1.0;
		bool getout = false;
		bool startout = false;
		const BspBrushSide* clipBrushSide = nullptr;

		for (int i = 0; i < brush.NumSides; i++)
		{
			const BspBrushSide& side = _brushSides[brush.FirstSide + i];
			const BspPlane& plane = _planes[side.PlaneNum];

			float dist = plane.Distance;

			if (!isPoint)
			{
				Vector3f ofs;

				for (int j = 0; j < 3; j++)
				{
					if (plane.Normal[j] < 0.0f)
					{
						ofs[j] = maxs[j];
					}
					else
					{
						ofs[j] = mins[j];
					}
				}

				dist -= Vector3f::Dot(ofs, plane.Normal);
			}
			else
			{
				dist = plane.Distance;
			}

			float d1 = Vector3f::Dot(start, plane.Normal) - dist;
			float d2 = Vector3f::Dot(end, plane.Normal) - dist;

			if (d2 > 0)
			{
				getout = true;
			}

			if (d1 > 0)
			{
				startout = true;
			}

			if (d1 > 0 && (d2 >= 0.125f || d2 >= d1))
			{
				return;
			}

			if (d1 <= 0 && d2 <= 0)
			{
				continue;
			}

			if (d1 > d2)
			{
				float f = (d1 - 0.125f) / (d1 - d2);

				if (f < 0)
				{
					f = 0;
				}

				if (f > enterFrac)
				{
					enterFrac = f;
					clipBrushSide = &side;
				}
			}
			else
			{
				float f = (d1 + 0.125f) / (d1 - d2);

				if (f > 1)
				{
					f = 1;
				}

				if (f < leaveFrac)
				{
					leaveFrac = f;
				}
			}
		}

		if (!startout)
		{
			trace.startSolid = true;

			if (!getout)
			{
				trace.allSolid = true;
				trace.fraction = 0;
			}

			return;
		}

		if (enterFrac < leaveFrac)
		{
			if (enterFrac > -1 && enterFrac < trace.fraction)
			{
				if (enterFrac < 0)
				{
					enterFrac = 0;
				}

				if (clipBrushSide)
				{
					const BspPlane& clipPlane = _planes[clipBrushSide->PlaneNum];
					const BspTextureInfo& clipTextureInfo = _textureInfo[clipBrushSide->TexInfo];

					trace.hit = true;
					trace.fraction = Math::Clamp(enterFrac, 0.0f, 1.0f);
					trace.planeNormal = clipPlane.Normal;
					trace.planeDistance = clipPlane.Distance;
					trace.axisU = Vector3f::Cross(clipPlane.Normal, clipTextureInfo.AxisU);

					if (trace.axisU.Length() <= 0.0f)
					{
						trace.axisU = Vector3f::Cross(clipPlane.Normal, clipTextureInfo.AxisV);
					}

					trace.axisU = trace.axisU.Normalise();
					trace.axisV = Vector3f::Cross(trace.axisU, clipPlane.Normal).Normalise();
				}
			}
		}
	}

	TraceResult Map::LineTrace(const Vector3f& start, const Vector3f& end, const BspContentFlags& brushMask)
	{
		return BoxTrace(start, end, 0, 0, brushMask);
	}

	TraceResult Map::BoxTrace(const Vector3f& start, const Vector3f& end, const Vector3f& mins, const Vector3f& maxs, const BspContentFlags& brushMask)
	{
		TraceResult trace = BoxTrace(start, end, mins, maxs, 0, brushMask);
		ClipBoxToEntities(start, end, mins, maxs, trace, brushMask);

		return trace;
	}

	void Map::ClipBoxToEntities(const Vector3f& start, const Vector3f& end, const Vector3f& mins, const Vector3f& maxs, TraceResult& tr, const BspContentFlags& brushMask)
	{
		for (const auto& entity : _worldEntities)
		{
			if (tr.allSolid)
			{
				return;
			}

			if (!entity->IsCollisionEnabled())
			{
				continue;
			}

			TraceResult trace;
			entity->Trace(start, end, mins, maxs, trace, brushMask);

			if (!trace.hit)
			{
				continue;
			}

			trace.entity = entity.get();

			if (trace.allSolid || trace.startSolid || trace.fraction < tr.fraction)
			{
				if (tr.startSolid)
				{
					tr = trace;
					tr.startSolid = true;
				}
				else
				{
					tr = trace;
				}
			}
			else if (trace.startSolid)
			{
				tr.startSolid = true;
			}
		}
	}

	TraceResult Map::LineTrace(const Vector3f& start, const Vector3f& end, int headNode, const BspContentFlags& brushMask)
	{
		return BoxTrace(start, end, 0, 0, headNode, brushMask);
	}

	TraceResult Map::BoxTrace(const Vector3f& start, const Vector3f& end, const Vector3f& mins, const Vector3f& maxs, int headNode, const BspContentFlags& brushMask)
	{
		Vector3f s(start.x, -start.z, start.y);
		Vector3f e(end.x, -end.z, end.y);

		TraceResult trace;
		std::memset(&trace, 0, sizeof(trace));
		trace.fraction = 1.0f;
		trace.hit = false;

		Vector3f extents;
		bool isPoint;

		if (mins[0] == 0 && mins[1] == 0 && mins[2] == 0 &&
			maxs[0] == 0 && maxs[1] == 0 && maxs[2] == 0)
		{
			isPoint = true;
			extents = Vector3f(0);
		}
		else
		{
			isPoint = false;
			extents = (maxs - mins);
		}

		trace.startPosition = s;
		trace.endPosition = e;

		RecursiveHullCheck(headNode, 0, 1, mins, maxs, s, e, trace, isPoint, extents, brushMask);

		trace.startPosition = Vector3f(trace.startPosition.x, trace.startPosition.z, -trace.startPosition.y);

		if (trace.hit)
		{
			trace.endPosition[0] = start[0] + trace.fraction * (end[0] - start[0]);
			trace.endPosition[1] = start[1] + trace.fraction * (end[1] - start[1]);
			trace.endPosition[2] = start[2] + trace.fraction * (end[2] - start[2]);
			trace.planeNormal = Vector3f(trace.planeNormal.x, trace.planeNormal.z, -trace.planeNormal.y).Normalise();
			trace.axisU = Vector3f(trace.axisU.x, trace.axisU.z, -trace.axisU.y);
			trace.axisV = Vector3f(trace.axisV.x, trace.axisV.z, -trace.axisV.y);
		}
		else
		{
			trace.endPosition = end;
		}

		return trace;
	}

	TraceResult Map::TransformedBoxTrace(
		const Vector3f& start,
		const Vector3f& end,
		const Vector3f& mins,
		const Vector3f& maxs,
		int headNode,
		const BspContentFlags& brushMask,
		const Vector3f& origin,
		const Quaternion& angles)
	{
		Vector3f startLocal = start - origin;
		Vector3f endLocal = end - origin;
		bool isRotated = (angles[0] || angles[1] || angles[2] || angles[3] != 1.0f);

		if (isRotated)
		{
			Quaternion anglesInverse = angles.Inverse();
			startLocal = anglesInverse * startLocal;
			endLocal = anglesInverse * endLocal;
		}

		TraceResult trace = BoxTrace(startLocal, endLocal, mins, maxs, headNode, brushMask);

		if (isRotated && trace.hit)
		{
			trace.planeNormal = angles * trace.planeNormal.Normalise();
			trace.axisU = angles * trace.axisU;
			trace.axisV = angles * trace.axisV;
		}

		trace.startPosition = start;
		trace.endPosition[0] = start[0] + trace.fraction * (end[0] - start[0]);
		trace.endPosition[1] = start[1] + trace.fraction * (end[1] - start[1]);
		trace.endPosition[2] = start[2] + trace.fraction * (end[2] - start[2]);

		return trace;
	}

	static void ClipVelocity(const Vector3f& in, const Vector3f& normal, Vector3f& out, float overbounce)
	{
		float backoff = Vector3f::Dot(in, normal) * overbounce;

		for (int i = 0; i < 3; i++)
		{
			float change = normal[i] * backoff;
			out[i] = in[i] - change;
		}

		if (float adjust = Vector3f::Dot(out, normal);
			adjust < 0.0f)
		{
			out -= (normal * adjust);
		}
	}

	bool Map::SlideMove(float time, Vector3f& origin, Vector3f& velocity, const Vector3f& mins, const Vector3f& maxs, const BspContentFlags& mask, bool gravity, bool grounded, const Vector3f& groundPlane)
	{
		int numBumps = 4;
		float remainingTime = time;
		Vector3f planes[5];
		int planeCount = 0;
		int bumpCount = 0;
		Vector3f clipVelocity;
		int i;

		if (!gravity)
		{
			planeCount = 1;
			planes[0] = groundPlane;
		}
		else
		{
			planeCount = 0;
		}

		planes[planeCount] = velocity.Normalise();
		planeCount++;

		for (bumpCount = 0; bumpCount < numBumps; bumpCount++)
		{
			Vector3f end = origin + velocity * remainingTime;
			TraceResult trace = BoxTrace(origin, end, mins, maxs, mask);

			if (trace.allSolid)
			{
				velocity[1] = 0;

				return true;
			}

			if (trace.fraction > 0)
			{
				origin = trace.endPosition;
			}

			if (trace.fraction == 1)
			{
				break;
			}

			remainingTime -= remainingTime * trace.fraction;

			{
				bool nearGround = grounded;

				if (!nearGround)
				{
					Vector3f stepEnd = origin + (Vector3f::Down * 18.0f);
					TraceResult downTrace = BoxTrace(origin, stepEnd, mins, maxs, mask);
					nearGround = (downTrace.fraction < 1.0f && downTrace.planeNormal[1] > 0.7f);
				}

				if (nearGround)
				{
					Vector3f stepEnd = origin - (Vector3f::Down * 18.0f);
					TraceResult downTrace = BoxTrace(origin, stepEnd, mins, maxs, mask);

					stepEnd = downTrace.endPosition + (velocity * remainingTime);
					TraceResult stepTrace = BoxTrace(downTrace.endPosition, stepEnd, mins, maxs, mask);

					stepEnd = stepTrace.endPosition + (Vector3f::Down * 18.0f);
					downTrace = BoxTrace(stepTrace.endPosition, stepEnd, mins, maxs, mask);

					if (downTrace.fraction >= 1.0f || downTrace.planeNormal[1] > 0.7f)
					{
						if (!stepTrace.hit)
						{
							remainingTime = 0;
							origin = downTrace.endPosition;

							break;
						}

						if (stepTrace.fraction > trace.fraction)
						{
							remainingTime -= remainingTime * stepTrace.fraction;
							origin = downTrace.endPosition;
							trace = stepTrace;
						}
					}
				}
			}

			if (planeCount >= 5)
			{
				velocity = 0;

				return true;
			}

			for (i = 0; i < planeCount; i++)
			{
				if (Vector3f::Dot(trace.planeNormal, planes[i]) > 0.99f)
				{
					velocity = trace.planeNormal + velocity;

					break;
				}
			}

			if (i < planeCount)
			{
				continue;
			}

			planes[planeCount] = trace.planeNormal;
			planeCount++;

			for (i = 0; i < planeCount; i++)
			{
				if (Vector3f::Dot(velocity, planes[i]) >= 0.1)
				{
					continue;
				}

				ClipVelocity(velocity, planes[i], clipVelocity, 1.001f);

				for (int j = 0; j < planeCount; j++)
				{
					if (j == i)
					{
						continue;
					}

					if (Vector3f::Dot(clipVelocity, planes[j]) >= 0.1f)
					{
						continue;
					}

					ClipVelocity(clipVelocity, planes[j], clipVelocity, 1.001f);

					if (Vector3f::Dot(clipVelocity, planes[i]) >= 0)
					{
						continue;
					}

					Vector3f dir = Vector3f::Cross(planes[i], planes[j]).Normalise();
					clipVelocity = dir * Vector3f::Dot(dir, velocity);

					for (int k = 0; k < planeCount; k++)
					{
						if (k == i || k == j)
						{
							continue;
						}

						if (Vector3f::Dot(clipVelocity, planes[k]) >= 0.1f)
						{
							continue;
						}

						velocity = 0;

						return true;
					}
				}

				velocity = clipVelocity;

				break;
			}
		}

		if (grounded)
		{
			Vector3f stepEnd = origin + Vector3f::Down * 18.0f;
			TraceResult downTrace = BoxTrace(origin, stepEnd, mins, maxs, mask);

			if (downTrace.hit && downTrace.fraction > 0.01f && downTrace.fraction < 1.0f)
			{
				origin = downTrace.endPosition;
			}
		}

		return (numBumps != 0);
	}
}
