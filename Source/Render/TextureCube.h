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
			GLsizei width;
			GLsizei height;
			GLenum internalFormat;
			GLenum format;
			GLenum type;
			std::vector<uint8_t> data;
		};

		static TextureCubeLibrary Library;

		TextureCube() = delete;
		TextureCube(const std::array<Image, 6>& faces);
		~TextureCube();

		virtual const GLuint GetHandle() const override { return _handle; }

	private:

		GLuint _handle;
	};
}
