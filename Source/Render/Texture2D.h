#pragma once

#include <glad/glad.h>

namespace Freeking
{
	class Texture2D
	{
	public:

		Texture2D() = delete;
		Texture2D(GLsizei width, GLsizei height, GLenum internalFormat, GLenum format, GLenum type, const void* data);
		~Texture2D();

		void Bind() const;
		void Bind(unsigned char slot) const;

		const GLuint GetHandle() const { return _handle; }
		const GLsizei GetWidth() const { return _width; }
		const GLsizei GetHeight() const { return _height; }

	private:

		GLuint _handle;
		GLsizei _width;
		GLsizei _height;
		GLenum _internalFormat;
		GLenum _format;
		GLenum _type;
		GLuint _sampler;
	};
}
