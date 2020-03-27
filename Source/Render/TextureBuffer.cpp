#include "TextureBuffer.h"
#include <memory>

namespace Freeking
{
	TextureBuffer::TextureBuffer(void* buffer, size_t length, GLenum format) :
		_id(0),
		_bufferId(0)
	{
		glGenTextures(1, &_id);
		glGenBuffers(1, &_bufferId);

		glBindBuffer(GL_TEXTURE_BUFFER, _bufferId);
		glBufferData(GL_TEXTURE_BUFFER, length, buffer, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);

		glBindTexture(GL_TEXTURE_BUFFER, _id);
		glTexBuffer(GL_TEXTURE_BUFFER, format, _bufferId);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}

	TextureBuffer::~TextureBuffer()
	{
		if (_bufferId != 0)
		{
			glDeleteBuffers(1, &_bufferId);
			_bufferId = 0;
		}

		if (_id != 0)
		{
			glDeleteTextures(1, &_id);
			_id = 0;
		}
	}

	void TextureBuffer::SetBuffer(void* buffer, size_t length)
	{
		glBindBuffer(GL_TEXTURE_BUFFER, _bufferId);
		glBufferSubData(GL_TEXTURE_BUFFER, 0, length, buffer);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
	}
}
