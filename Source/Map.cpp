#include "Map.h"
#include "Lightmap.h"
#include "Texture2D.h"
#include "BspFile.h"
#include "BspFlags.h"
#include "Util.h"
#include "Mesh.h"
#include "Paths.h"
#include <array>

namespace Freeking
{
	void Map::Render(const Matrix4x4& viewProjection)
	{
		_shader->Bind();
		_shader->SetUniformValue("viewProj", viewProjection);
		_shader->SetUniformValue("diffuse", 0);
		_shader->SetUniformValue("lightmap", 1);
		_shader->SetUniformValue("brightness", 2.0f);

		_textureSampler->Bind(0);
		_lightmapSampler->Bind(1);

		for (auto& mesh : _meshes)
		{
			mesh.second->Draw();
		}

		_shader->Unbind();
	}

	Map::Map(const BspFile& bspFile)
	{
		auto entities = bspFile.GetLumpArray<char>(bspFile.Header.Entities);
		auto vertices = bspFile.GetLumpArray<Vector3f>(bspFile.Header.Vertices);
		auto models = bspFile.GetLumpArray<BspModel>(bspFile.Header.Models);
		auto faces = bspFile.GetLumpArray<BspFace>(bspFile.Header.Faces);
		auto edges = bspFile.GetLumpArray<BspEdge>(bspFile.Header.Edges);
		auto faceEdges = bspFile.GetLumpArray<int32_t>(bspFile.Header.FaceEdges);
		auto planes = bspFile.GetLumpArray<BspPlane>(bspFile.Header.Planes);
		auto textureInfo = bspFile.GetLumpArray<BspTextureInfo>(bspFile.Header.TextureInfo);
		auto lightmapData = bspFile.GetLumpArray<uint8_t>(bspFile.Header.Lightmaps);

		std::string entityString(entities.Data(), entities.Num());
		_entityLump = std::make_unique<EntityLump>(entityString);

		for (int i = 0; i < textureInfo.Num(); ++i)
		{
			const auto& texInfo = textureInfo[i];
			auto path = Paths::KingpinDir() / "main/textures" / (std::string(texInfo.TextureName) + std::string(".tga"));
			_textures.push_back(Util::LoadTexture(path.string()));
		}

		int lmSize = 1024;
		auto lightmapImage = std::make_shared<LightmapImage>(lmSize, lmSize);
		auto lmRootNode = std::make_shared<LightmapNode>(0, 0, lmSize, lmSize);

		std::array<uint8_t, (16 * 16) * 3> blackPixels = { 0 };
		auto blackLightmapNode = Map::ReadLightmap(*lightmapImage, lmRootNode, 0, 16, 16, blackPixels.data());
		Vector2f blackLightmapUV(8.0f / lightmapImage->GetWidth(), 8.0f / lightmapImage->GetHeight());

		for (int modelIndex = 0; modelIndex < models.Num(); ++modelIndex)
		{
			if (modelIndex > 0)
			{
				break;
			}

			const auto& brushModel = models[modelIndex];

			for (int faceIndex = brushModel.FirstFace; faceIndex < (brushModel.FirstFace + brushModel.NumFaces); ++faceIndex)
			{
				const auto& face = faces[faceIndex];
				const auto& faceTextureInfo = textureInfo[face.TextureInfo];

				if ((faceTextureInfo.Flags & (int)BspSurfaceFlags::SURF_NODRAW) ||
					(faceTextureInfo.Flags & (int)BspSurfaceFlags::SURF_SKY) ||
					(faceTextureInfo.Flags & (int)BspSurfaceFlags::SURF_WARP))
				{
					continue;
				}

				Mesh* mesh = nullptr;

				if (_meshes.find(face.TextureInfo) == _meshes.end())
				{
					auto newMesh = std::make_unique<Mesh>();
					newMesh->SetDiffuse(_textures[face.TextureInfo]);
					_meshes.insert(std::make_pair(face.TextureInfo, std::move(newMesh)));
				}

				mesh = _meshes[face.TextureInfo].get();

				if (mesh == nullptr)
				{
					continue;
				}

				float umin = std::numeric_limits<float>::max();
				float vmin = std::numeric_limits<float>::max();
				float umax = std::numeric_limits<float>::lowest();
				float vmax = std::numeric_limits<float>::lowest();

				int baseVertex = mesh->GetNumVertices();

				std::vector<Mesh::Vertex> faceVertices;
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

					u /= (float)_textures[face.TextureInfo]->GetWidth();
					v /= (float)_textures[face.TextureInfo]->GetHeight();

					faceVertices[edgeIndex] = { position, normal, { Vector2f(u, v), blackLightmapUV, blackLightmapUV } };
				}

				if (face.LightmapOffset != 0)
				{
					float lminu = floor(umin / 16.0f);
					float lmaxu = ceil(umax / 16.0f);
					float lminv = floor(vmin / 16.0f);
					float lmaxv = ceil(vmax / 16.0f);

					int lwidth = (int)(lmaxu - lminu + 1);
					int lheight = (int)(lmaxv - lminv + 1);

					for (int lightStyleIndex = 0; lightStyleIndex < 2; ++lightStyleIndex)
					{
						auto lightStyle = face.LightmapStyles[lightStyleIndex];
						if (lightStyle == 255)
						{
							continue;
						}

						auto lightmapOffset = face.LightmapOffset + (((lwidth * lheight) * 3) * lightStyleIndex);
						auto rect = Map::ReadLightmap(*lightmapImage, lmRootNode, lightmapOffset, lwidth, lheight, lightmapData.Data());

						if (rect)
						{
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

								ucoord = ((ucoord * lwidth) + rect->GetX()) / lightmapImage->GetWidth();
								vcoord = ((vcoord * lheight) + rect->GetY()) / lightmapImage->GetHeight();

								vertex.UV[uvIndex].x = ucoord;
								vertex.UV[uvIndex].y = vcoord;
							}
						}
					}
				}

				for (size_t i = 0; i < faceVertices.size(); ++i)
				{
					mesh->AddVertex(faceVertices[i]);
				}

				int numTriangles = face.NumEdges - 2;

				for (int triangleIndex = 0; triangleIndex < numTriangles; ++triangleIndex)
				{
					uint32_t baseIndex = baseVertex + triangleIndex;
					mesh->AddIndex(baseIndex + 2);
					mesh->AddIndex(baseIndex + 1);
					mesh->AddIndex(baseVertex);
				}
			}
		}

		_lightmapTexture = std::make_shared<Texture2D>(
			lmSize,
			lmSize,
			GL_RGBA,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			lightmapImage->Data.data());

		for (auto& mesh : _meshes)
		{
			mesh.second->SetLightmap(_lightmapTexture);
			mesh.second->Commit();
		}

		_shader = Util::LoadShader("Shaders/Mesh.vert", "Shaders/Mesh.frag");
		_textureSampler = std::make_shared<TextureSampler>(WrapMode::WRAPMODE_REPEAT, FilterMode::FILTERMODE_LINEAR);
		_lightmapSampler = std::make_shared<TextureSampler>(WrapMode::WRAPMODE_CLAMP_EDGE, FilterMode::FILTERMODE_LINEAR_NO_MIP);
	}

	std::shared_ptr<LightmapNode> Map::ReadLightmap(LightmapImage& image, std::shared_ptr<LightmapNode>& root, int offset, int width, int height, const uint8_t* buffer)
	{
		if (height <= 0 || width <= 0)
		{
			return nullptr;
		}

		auto node = LightmapNode::Allocate(root, width, height);
		if (node)
		{
			for (int x = 0; x < width; ++x)
			{
				for (int y = 0; y < height; ++y)
				{
					int dstPixel = ((node->GetY() + y) * image.GetWidth()) + (node->GetX() + x);
					int dstIndex = dstPixel * 3;
					int srcPixel = (y * width) + x;
					int srcIndex = offset + (srcPixel * 3);

					image.Data[dstIndex] = buffer[srcIndex];
					image.Data[dstIndex + 1] = buffer[srcIndex + 1];
					image.Data[dstIndex + 2] = buffer[srcIndex + 2];
				}
			}
		}

		return node;
	}
}
