#include "Md2Loader.h"
#include "KeyframeModel.h"
#include "Md2File.h"

namespace Freeking
{
	bool MD2Loader::CanLoadExtension(const std::string& extension) const
	{
		if (extension == ".md2") return true;

		return false;
	};

	MD2Loader::AssetPtr MD2Loader::Load(const std::string& name) const
	{
		if (auto buffer = FileSystem::GetFileData(name); !buffer.empty())
		{
			const auto& file = MD2File::Create(buffer.data());
			if (!file.IsValid())
			{
				return nullptr;
			}

			auto mesh = std::make_shared<KeyframeMesh>();

			uint32_t pos = file.Header.OffsetFrames;
			for (int frameIndex = 0; frameIndex < file.Header.NumFrames; ++frameIndex)
			{
				auto frame = file.Read<MD2Frame>(pos, 1);
				auto vertices = file.Read<MD2Vertex>(pos, file.Header.NumVertices);
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
							(int8_t)(vertex.X - 128),
							(int8_t)(vertex.Y - 128),
							(int8_t)(vertex.Z - 128),
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
				auto command = file.Read<MD2Command>(pos, 1);
				if (command->TrisTypeNum == 0)
				{
					break;
				}

				auto numCommandVertices = abs(command->TrisTypeNum);

				for (int commandVertexIndex = 0; commandVertexIndex < numCommandVertices; ++commandVertexIndex)
				{
					auto commandVertex = file.Read<MD2CommandVertex>(pos, 1);
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
				const auto& skin = file.Read<MD2Skin>(pos, 1);
				std::string skinName((char*)skin->Path.data());
				mesh->Skins.push_back(skinName);
			}

			return mesh;
		}

		return nullptr;
	}
}
