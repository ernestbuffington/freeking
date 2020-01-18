#include "TextureBuffer.h"

namespace Freeking
{
	TextureBuffer::TextureBuffer(void* buffer, size_t length, GLenum format) :
		_handle(0),
		_bufferHandle(0)
	{
		glGenTextures(1, &_handle);
		glGenBuffers(1, &_bufferHandle);

		glBindBuffer(GL_TEXTURE_BUFFER, _bufferHandle);
		glBufferData(GL_TEXTURE_BUFFER, length, buffer, GL_STATIC_READ);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);

		glBindTexture(GL_TEXTURE_BUFFER, _handle);
		glTexBuffer(GL_TEXTURE_BUFFER, format, _bufferHandle);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}

	TextureBuffer::~TextureBuffer()
	{
		if (_bufferHandle != 0)
		{
			glDeleteBuffers(1, &_bufferHandle);
			_bufferHandle = 0;
		}

		if (_handle != 0)
		{
			glDeleteTextures(1, &_handle);
			_handle = 0;
		}
	}

	void TextureBuffer::Bind(uint32_t slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_BUFFER, _handle);
	}

	void TextureBuffer::Unbind()
	{
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}
}
