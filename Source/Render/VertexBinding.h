#pragma once

#include <cstddef>
#include <cstdint>
#include <glad/glad.h>

namespace Freeking
{
	class VertexBuffer;
	class IndexBuffer;

	enum class ElementType
	{
		Float = GL_FLOAT,
		Int = GL_INT,
		UByte = GL_UNSIGNED_BYTE,
		UInt = GL_UNSIGNED_INT,
		UShort = GL_UNSIGNED_SHORT,
	};

	struct ArrayElement
	{
		ArrayElement(
			const VertexBuffer* buffer,
			std::size_t attributeIndex,
			std::size_t componentCount,
			ElementType type,
			std::size_t stride,
			std::size_t offset,
			std::size_t instanceStep = 0);

		const VertexBuffer* buffer;
		std::size_t attributeIndex;
		std::size_t componentCount;
		ElementType type;
		std::size_t stride;
		std::size_t offset;
		std::size_t instanceStep;
	};

	class VertexBinding
	{
	public:

		explicit VertexBinding();
		~VertexBinding();

		void Create(const ArrayElement* elements, std::size_t elementCount, const VertexBuffer& vertices);
		void Create(const ArrayElement* elements, std::size_t elementCount, const IndexBuffer& indices, ElementType indicesType);
		void Dispose();
		void Bind();
		void Unbind();

		inline int GetNumElements() const { return _numElements; }
		inline bool HasIndices() const { return _hasIndices; }
		inline ElementType GetIndexType() const { return _indicesType; }

	private:

		void CreateVAO();
		void SetupVertices(const ArrayElement* elements, std::size_t elementCount);
		void SetupIndices(const IndexBuffer& indices, ElementType indicesType);

		GLuint _handle;
		ElementType _indicesType;
		bool _hasIndices;
		int _numElements;
	};
}
