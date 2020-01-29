#include "Texture2D.h"
#include "TextureLoader.h"
#include "ThirdParty/stb/stb_image.h"

namespace Freeking
{
	void TextureLibrary::UpdateLoaders()
	{
		AddLoader<TextureLoader>();
	}

	TextureLibrary Texture2D::Library;

	Texture2D::Texture2D(GLsizei width, GLsizei height, GLenum internalFormat, GLenum format, GLenum type, const void* data) :
		_width(width),
		_height(height),
		_internalFormat(internalFormat),
		_format(format),
		_type(type),
		_handle(0)
	{
		glGenTextures(1, &_handle);
		glBindTexture(GL_TEXTURE_2D, _handle);
		glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _format, _type, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture2D::~Texture2D()
	{
		if (_handle != 0)
		{
			glDeleteTextures(1, &_handle);
		}
	}

	void Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, _handle);
	}

	void Texture2D::Bind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, _handle);
	}
}
