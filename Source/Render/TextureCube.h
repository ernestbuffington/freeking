#pragma once

#include "Texture.h"
#include "AssetLibrary.h"
#include <array>
#include <vector>
#include <glad/gl.h>

namespace Freeking
{
	class TextureCube;

	class TextureCubeLibrary : public AssetLibrary<TextureCube>
	{
	};

	class TextureCube : public Texture
	{
	public:

		struct Image
		{
			GLsizei width = 0;
			GLsizei height = 0;
			GLenum internalFormat = GL_INVALID_ENUM;
			GLenum format = GL_INVALID_ENUM;
			GLenum type = GL_INVALID_ENUM;
			std::vector<uint8_t> data;
		};

		static TextureCubeLibrary Library;

		TextureCube() = delete;
		TextureCube(const std::array<Image, 6>& faces);
		~TextureCube();

		virtual const GLuint GetId() const override { return _id; }

	private:

		GLuint _id;
	};
}
