#include "MdxLoader.h"
#include "DynamicModel.h"
#include "MdxFile.h"

namespace Freeking
{
	bool MDXLoader::CanLoadExtension(const std::string& extension) const
	{
		if (extension == ".mdx") return true;

		return false;
	};

	MDXLoader::AssetPtr MDXLoader::Load(const std::string& name) const
	{
		if (auto buffer = FileSystem::GetFileData(name); !buffer.empty())
		{
			const auto& file = MDXFile::Create(buffer.data());
			if (!file.IsValid())
			{
				return nullptr;
			}

			auto mesh = std::make_shared<DynamicModel>();

			uint32_t pos = file.Header.OffsetFrames;
			for (int frameIndex = 0; frameIndex < file.Header.NumFrames; ++frameIndex)
			{
				auto frame = file.Read<MDXFrame>(pos, 1);
				auto vertices = file.Read<MDXVertex>(pos, file.Header.NumVertices);
				std::string frameName((char*)frame->Name.data());

				mesh->FrameTransforms.push_back(
					{
						frameName,
						Vector3f(frame->Translate[0], frame->Translate[1], frame->Translate[2]),
						Vector3f(frame->Scale[0], frame->Scale[1], frame->Scale[2])
					});

				for (int vertexIndex = 0; vertexIndex < file.Header.NumVertices; ++vertexIndex)
				{
					const auto& vertex = vertices[vertexIndex];

					mesh->FrameVertices.push_back(
						{
							(int8_t)(vertex.Vertex[0] - 128),
							(int8_t)(vertex.Vertex[1] - 128),
							(int8_t)(vertex.Vertex[2] - 128),
							(int8_t)(vertex.NormalIndex - 128)
						});
				}
			}

			mesh->SetFrameCount(file.Header.NumFrames);
			mesh->SetFrameVertexCount(file.Header.NumVertices);

			uint32_t vertexOffset = 0;

			pos = file.Header.OffsetCommands;
			for (int commandIndex = 0; commandIndex < file.Header.NumCommands; ++commandIndex)
			{
				auto command = file.Read<MDXCommand>(pos, 1);
				if (command->TrisTypeNum == 0)
				{
					break;
				}

				auto numCommandVertices = abs(command->TrisTypeNum);

				if (mesh->SubObjects.size() == command->SubObjectID)
				{
					mesh->SubObjects.push_back({ (int)mesh->Indices.size(), 0 });
				}
				
				mesh->SubObjects.back().numIndices += (numCommandVertices - 2) * 3;

				for (int commandVertexIndex = 0; commandVertexIndex < numCommandVertices; ++commandVertexIndex)
				{
					auto commandVertex = file.Read<MDXCommandVertex>(pos, 1);
					Vector2f uv(commandVertex->TextureCoordinates[0], commandVertex->TextureCoordinates[1]);

					mesh->Vertices.push_back(
						{
							uv,
							commandVertex->VertexIndex
						});
				}

				for (int vertexIndex = 0; vertexIndex < numCommandVertices - 2; ++vertexIndex)
				{
					if (command->TrisTypeNum < 0)
					{
						mesh->Indices.emplace_back(vertexOffset + (vertexIndex + 2));
						mesh->Indices.emplace_back(vertexOffset + (vertexIndex + 1));
						mesh->Indices.emplace_back(vertexOffset);
					}
					else if ((vertexIndex % 2) == 0)
					{
						mesh->Indices.emplace_back(vertexOffset + (vertexIndex + 2));
						mesh->Indices.emplace_back(vertexOffset + (vertexIndex + 1));
						mesh->Indices.emplace_back(vertexOffset + vertexIndex);
					}
					else
					{
						mesh->Indices.emplace_back(vertexOffset + vertexIndex);
						mesh->Indices.emplace_back(vertexOffset + (vertexIndex + 1));
						mesh->Indices.emplace_back(vertexOffset + (vertexIndex + 2));
					}
				}

				vertexOffset += numCommandVertices;
			}

			pos = file.Header.OffsetSkins;
			for (int skinIndex = 0; skinIndex < file.Header.NumSkins; ++skinIndex)
			{
				const auto& skin = file.Read<MDXSkin>(pos, 1);
				std::string skinName((char*)skin->Path.data());
				mesh->Skins.push_back(skinName);
			}

			mesh->FrameBounds.resize(file.Header.NumSubObjects);

			pos = file.Header.OffsetBBoxFrames;
			for (int subObjectIndex = 0; subObjectIndex < file.Header.NumSubObjects; ++subObjectIndex)
			{
				auto& subObjectBounds = mesh->FrameBounds.at(subObjectIndex);
				subObjectBounds.resize(file.Header.NumFrames);

				for (int frameIndex = 0; frameIndex < file.Header.NumFrames; ++frameIndex)
				{
					const auto& bbox = file.Read<MDXBBox>(pos, 1);
					auto& frameBounds = subObjectBounds.at(frameIndex);
					frameBounds.boundsMin = Vector3f(bbox->MinX, bbox->MinZ, -bbox->MinY);
					frameBounds.boundsMax = Vector3f(bbox->MaxX, bbox->MaxZ, -bbox->MaxY);
				}
			}

			mesh->Commit();

			return mesh;
		}

		return nullptr;
	}
}
