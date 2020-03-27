#pragma once

#include "Texture.h"

namespace Freeking
{
	class TextureBuffer : public Texture
	{

	public:

		TextureBuffer(void* buffer, size_t length, GLenum format);
		~TextureBuffer();

		void SetBuffer(void* buffer, size_t length);

		virtual const GLuint GetId() const override { return _id; }

	protected:

		GLuint _id;
		GLuint _bufferId;
	};
}
