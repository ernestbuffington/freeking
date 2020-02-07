#include "VertexBuffer.h"
#include <cassert>

namespace Freeking
{
	VertexBuffer::VertexBuffer(const void* vertices, std::size_t vertexCount, size_t strideBytes, GLuint hint) :
		_vbo(0),
		_vertexCount(vertexCount),
		_strideBytes(strideBytes),
		_hint(hint)
	{
		assert(vertexCount > 0);
		assert(strideBytes > 0);

		glGenBuffers(1, &_vbo);

		if (glGetError() == GL_NO_ERROR)
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER, vertexCount * strideBytes, vertices, _hint);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else
		{
			_vbo = 0;
		}
	}

	VertexBuffer::~VertexBuffer()
	{
		if (_vbo)
		{
			glDeleteBuffers(1, &_vbo);
		}
	}

	void VertexBuffer::UpdateBuffer(const void* data, size_t offset, size_t size)
	{
		if (_vbo)
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	std::size_t VertexBuffer::GetVertexCount() const noexcept
	{
		return _vertexCount;
	}

	std::size_t VertexBuffer::GetStrideBytes() const noexcept
	{
		return _strideBytes;
	}

	std::size_t VertexBuffer::GetSizeInBytes() const noexcept
	{
		return _vertexCount * _strideBytes;
	}

	GLuint VertexBuffer::GetHint() const noexcept
	{
		return _hint;
	}

	GLuint VertexBuffer::GetVBO() const noexcept
	{
		return _vbo;
	}

}
