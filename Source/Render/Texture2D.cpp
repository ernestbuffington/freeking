#include "Texture2D.h"
#include "TextureLoader.h"
#include "ThirdParty/stb/stb_image.h"
#include <algorithm>

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
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _format, _type, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture2D::Texture2D(GLsizei width, GLsizei height, uint8_t r, uint8_t g, uint8_t b) :
		_width(width),
		_height(height),
		_internalFormat(GL_RGBA8),
		_format(GL_RGB),
		_type(GL_UNSIGNED_BYTE),
		_handle(0)
	{
		std::vector<uint8_t> buffer((width * height) * 3, 0);
		uint8_t pixel[] { r, g, b };
		for (auto i = 0; i < width * height; ++i)
		{
			std::memcpy(&buffer[i * 3], pixel, 3);
		}

		glGenTextures(1, &_handle);
		glBindTexture(GL_TEXTURE_2D, _handle);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _format, _type, (void*)buffer.data());
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
