#include "MdxFile.h"
#include "NormalTable.h"

namespace Freeking
{
	struct FrameVertex
	{
		Vector3f Position;
		Vector3f Normal;
	};

	void MDXFile::Build(std::shared_ptr<KeyframeMesh>& mesh) const
	{
		if (!IsValid())
		{
			return;
		}

		uint32_t pos = Header.OffsetFrames;
		for (int frameIndex = 0; frameIndex < Header.NumFrames; ++frameIndex)
		{
			auto frame = Read<MDXFrame>(pos, 1);
			auto vertices = Read<MDXVertex>(pos, Header.NumVertices);
			std::string frameName((char*)frame->Name.data());

			mesh->FrameTransforms.push_back(
				{
					frameName,
					Vector3f(frame->Translate[0], frame->Translate[1], frame->Translate[2]),
					Vector3f(frame->Scale[0], frame->Scale[1], frame->Scale[2])
				});

			for (int vertexIndex = 0; vertexIndex < Header.NumVertices; ++vertexIndex)
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

		mesh->SetFrameCount(Header.NumFrames);
		mesh->SetFrameVertexCount(Header.NumVertices);

		uint32_t vertexOffset = 0;

		pos = Header.OffsetCommands;
		for (int commandIndex = 0; commandIndex < Header.NumCommands; ++commandIndex)
		{
			auto command = Read<MDXCommand>(pos, 1);
			if (command->TrisTypeNum == 0)
			{
				break;
			}

			auto numCommandVertices = abs(command->TrisTypeNum);

			for (int commandVertexIndex = 0; commandVertexIndex < numCommandVertices; ++commandVertexIndex)
			{
				auto commandVertex = Read<MDXCommandVertex>(pos, 1);
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
					mesh->AddIndex(vertexOffset + (vertexIndex + 2));
					mesh->AddIndex(vertexOffset + (vertexIndex + 1));
					mesh->AddIndex(vertexOffset);
				}
				else if ((vertexIndex % 2) == 0)
				{
					mesh->AddIndex(vertexOffset + (vertexIndex + 2));
					mesh->AddIndex(vertexOffset + (vertexIndex + 1));
					mesh->AddIndex(vertexOffset + vertexIndex);
				}
				else
				{
					mesh->AddIndex(vertexOffset + vertexIndex);
					mesh->AddIndex(vertexOffset + (vertexIndex + 1));
					mesh->AddIndex(vertexOffset + (vertexIndex + 2));
				}
			}

			vertexOffset += numCommandVertices;
		}

		pos = Header.OffsetSkins;
		for (int skinIndex = 0; skinIndex < Header.NumSkins; ++skinIndex)
		{
			const auto& skin = Read<MDXSkin>(pos, 1);
			std::string skinName((char*)skin->Path.data());
			mesh->Skins.push_back(skinName);
		}
	}
}
