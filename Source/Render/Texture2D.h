#pragma once

#include "Texture.h"
#include "AssetLibrary.h"
#include <glad/gl.h>

namespace Freeking
{
	class Texture2D;

	class TextureLibrary : public AssetLibrary<Texture2D>
	{
	protected:

		virtual void UpdateLoaders() override;
	};

	class Texture2D : public Texture
	{
	public:

		static TextureLibrary Library;

		Texture2D() = delete;
		Texture2D(GLsizei width, GLsizei height, GLenum internalFormat, GLenum format, GLenum type, const void* data);
		Texture2D(GLsizei width, GLsizei height, uint8_t r, uint8_t g, uint8_t b);
		~Texture2D();

		virtual const GLuint GetId() const override { return _id; }
		const GLsizei GetWidth() const { return _width; }
		const GLsizei GetHeight() const { return _height; }

	private:

		GLuint _id;
		GLsizei _width;
		GLsizei _height;
		GLenum _internalFormat;
		GLenum _format;
		GLenum _type;
	};
}
