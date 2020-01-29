#include "StaticModel.h"
#include "NormalTable.h"
#include "Md2Loader.h"
#include "MdxLoader.h"

namespace Freeking
{
	void StaticModelLibrary::UpdateLoaders()
	{
	}

	StaticModelLibrary StaticModel::Library;

	void StaticModel::Commit()
	{
		static const int vertexSize = sizeof(Vertex);

		_indexBuffer = std::make_unique<IndexBuffer>(Indices.data(), Indices.size(), GL_UNSIGNED_INT);
		_vertexBuffer = std::make_unique<VertexBuffer>(Vertices.data(), Vertices.size(), vertexSize, GL_STATIC_DRAW);

		ArrayElement vertexLayout[] =
		{
			ArrayElement(_vertexBuffer.get(), 0, 3, ElementType::Float, vertexSize, 0),
			ArrayElement(_vertexBuffer.get(), 1, 3, ElementType::Float, vertexSize, 3 * sizeof(float)),
			ArrayElement(_vertexBuffer.get(), 1, 2, ElementType::Float, vertexSize, 6 * sizeof(float)),
		};

		_vertexBinding = std::make_unique<VertexBinding>();
		_vertexBinding->Create(vertexLayout, 3, *_indexBuffer, ElementType::UInt);
	}
}
