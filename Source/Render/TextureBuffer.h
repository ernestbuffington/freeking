#pragma once

#include "Texture.h"

namespace Freeking
{
	class TextureBuffer : public Texture
	{

	public:

		TextureBuffer(void* buffer, size_t length, GLenum format);
		~TextureBuffer();

		virtual const GLuint GetHandle() const override { return _handle; }

	protected:

		GLuint _handle;
		GLuint _bufferHandle;
	};
}
