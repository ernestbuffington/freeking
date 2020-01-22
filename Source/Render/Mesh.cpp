#include "Mesh.h"
#include "NormalTable.h"

namespace Freeking
{
	void BrushMesh::Draw()
	{
		if (_diffuse)
		{
			_diffuse->Bind(0);
		}

		if (_lightmap)
		{
			_lightmap->Bind(1);
		}

		_vertexBinding->Bind();
		glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, (void*)0);
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
			ArrayElement(_vertexBuffer.get(), 0, 3, ElementType::AE_FLOAT, vertexSize, 0),
			ArrayElement(_vertexBuffer.get(), 1, 3, ElementType::AE_FLOAT, vertexSize, 3 * sizeof(float)),
			ArrayElement(_vertexBuffer.get(), 2, 2, ElementType::AE_FLOAT, vertexSize, 6 * sizeof(float)),
			ArrayElement(_vertexBuffer.get(), 3, 2, ElementType::AE_FLOAT, vertexSize, 8 * sizeof(float)),
			ArrayElement(_vertexBuffer.get(), 4, 2, ElementType::AE_FLOAT, vertexSize, 10 * sizeof(float)),
		};

		_vertexBinding = std::make_unique<VertexBinding>();
		_vertexBinding->Create(vertexLayout, 5, *_indexBuffer, ElementType::AE_UINT);
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

		if (_normalBuffer)
		{
			_normalBuffer->Bind(2);
		}

		_vertexBinding->Bind();
		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (void*)0);
		_vertexBinding->Unbind();
	}

	void KeyframeMesh::Commit()
	{
		static const int vertexSize = sizeof(Vertex);

		_indexBuffer = std::make_unique<IndexBuffer>(_indices.data(), _indices.size(), GL_UNSIGNED_INT);
		_vertexBuffer = std::make_unique<VertexBuffer>(Vertices.data(), Vertices.size(), vertexSize, GL_STATIC_DRAW);
		_frameVertexBuffer = std::make_unique<TextureBuffer>(FrameVertices.data(), FrameVertices.size() * sizeof(FrameVertex), GL_RGBA8I);
		_normalBuffer = std::make_unique<TextureBuffer>((void*)&NormalTable[0][0], (162 * 3) * sizeof(float), GL_RGB32F);

		ArrayElement vertexLayout[] =
		{
			ArrayElement(_vertexBuffer.get(), 0, 2, ElementType::AE_FLOAT, vertexSize, 0),
			ArrayElement(_vertexBuffer.get(), 1, 1, ElementType::AE_INT, vertexSize, 2 * sizeof(float)),
		};

		_vertexBinding = std::make_unique<VertexBinding>();
		_vertexBinding->Create(vertexLayout, 2, *_indexBuffer, ElementType::AE_UINT);
	}

	void KeyframeMesh::AddIndex(uint32_t index)
	{
		_indices.push_back(index);
	}

	void KeyframeMesh::SetDiffuse(const std::shared_ptr<Texture2D>& texture)
	{
		_diffuse = texture;
	}
}
