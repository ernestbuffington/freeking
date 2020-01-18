#pragma once

#include <glad/glad.h>
#include <vector>

namespace Freeking
{
	class TextureBuffer
	{

	public:

		TextureBuffer(void* buffer, size_t length, GLenum format);
		~TextureBuffer();

		void Bind(uint32_t slot);
		void Unbind();

	protected:

		GLuint _handle;
		GLuint _bufferHandle;
	};
}
