#include "Texture2D.h"
#include "Util.h"
#include "ThirdParty/stb/stb_image.h"

namespace Freeking
{
	class TextureLoader : public AssetLoader<Texture2D>
	{
	public:

		virtual bool CanLoadExtension(const std::string& extension) const override
		{
			if (extension == ".png") return true;
			if (extension == ".jpg") return true;
			if (extension == ".jpeg") return true;
			if (extension == ".tga") return true;
			if (extension == ".bmp") return true;
			if (extension == ".psd") return true;

			return false;
		};

		virtual AssetPtr Load(const std::string& name) const override
		{
			if (auto buffer = FileSystem::GetFileData(name); !buffer.empty())
			{
				int imageWidth, imageHeight, imageChannels;
				if (uint8_t* image = stbi_load_from_memory(
					(uint8_t*)buffer.data(), (std::int32_t)buffer.size(),
					&imageWidth, &imageHeight, &imageChannels, 0))
				{
					auto texture = std::make_shared<Texture2D>(
						imageWidth, imageHeight,
						GL_RGBA, imageChannels == 3 ? GL_RGB : GL_RGBA,
						GL_UNSIGNED_BYTE,
						image);

					stbi_image_free(image);

					return texture;
				}
			}

			return nullptr;
		}
	};

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

	void Texture2D::Bind(unsigned char slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, _handle);
	}
}
