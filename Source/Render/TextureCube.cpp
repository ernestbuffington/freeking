#include "TextureCube.h"

namespace Freeking
{
	TextureCubeLibrary TextureCube::Library;

	TextureCube::TextureCube(const std::array<Image, 6>& faces)
	{
		glGenTextures(1, &_handle);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);

		for (size_t i = 0; i < faces.size(); i++)
		{
			const auto& face = faces[i];
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				face.internalFormat,
				face.width, face.height,
				0,
				face.format,
				face.type,
				face.data.data());
		}

		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}

	TextureCube::~TextureCube()
	{
		if (_handle)
		{
			glDeleteTextures(1, &_handle);
		}
	}
}
