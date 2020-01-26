#include "KeyframeModel.h"
#include "NormalTable.h"

namespace Freeking
{
	static const std::unique_ptr<TextureBuffer>& GetNormalBuffer()
	{
		static auto normalBuffer = std::make_unique<TextureBuffer>((void*)&NormalTable[0][0], (162 * 3) * sizeof(float), GL_RGB32F);
		return normalBuffer;
	}

	void KeyframeMesh::Draw()
	{
		if (_diffuse)
		{
			_diffuse->Bind(0);
		}

		if (_frameVertexBuffer)
		{
			_frameVertexBuffer->Bind(1);
		}

		GetNormalBuffer()->Bind(2);

		_vertexBinding->Bind();
		glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, (void*)0);
		_vertexBinding->Unbind();
	}

	void KeyframeMesh::Commit()
	{
		static const int vertexSize = sizeof(Vertex);

		_indexBuffer = std::make_unique<IndexBuffer>(Indices.data(), Indices.size(), GL_UNSIGNED_INT);
		_vertexBuffer = std::make_unique<VertexBuffer>(Vertices.data(), Vertices.size(), vertexSize, GL_STATIC_DRAW);
		_frameVertexBuffer = std::make_unique<TextureBuffer>(FrameVertices.data(), FrameVertices.size() * sizeof(FrameVertex), GL_RGBA8I);

		ArrayElement vertexLayout[] =
		{
			ArrayElement(_vertexBuffer.get(), 0, 2, ElementType::AE_FLOAT, vertexSize, 0),
			ArrayElement(_vertexBuffer.get(), 1, 1, ElementType::AE_INT, vertexSize, 2 * sizeof(float)),
		};

		_vertexBinding = std::make_unique<VertexBinding>();
		_vertexBinding->Create(vertexLayout, 2, *_indexBuffer, ElementType::AE_UINT);
	}

	void KeyframeMesh::SetDiffuse(const std::shared_ptr<Texture2D>& texture)
	{
		_diffuse = texture;
	}
}
