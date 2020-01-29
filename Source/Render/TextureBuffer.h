#pragma once

#include "Texture2D.h"
#include <glad/glad.h>
#include <vector>

namespace Freeking
{
	class TextureBuffer : public Texture
	{

	public:

		TextureBuffer(void* buffer, size_t length, GLenum format);
		~TextureBuffer();

		void Bind(uint32_t slot);
		void Unbind();

		virtual const GLuint GetHandle() const override { return _handle; }

	protected:

		GLuint _handle;
		GLuint _bufferHandle;
	};
}
