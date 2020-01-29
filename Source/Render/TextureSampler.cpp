#include "TextureSampler.h"

namespace Freeking
{
	static int WrapModes[2] =
	{
		GL_REPEAT,
		GL_CLAMP_TO_EDGE,
	};

	static int FilterModesMin[4] =
	{
		GL_LINEAR_MIPMAP_LINEAR,
		GL_NEAREST_MIPMAP_NEAREST,
		GL_LINEAR,
		GL_NEAREST,
	};

	static int FilterModesMag[4] =
	{
		GL_LINEAR,
		GL_NEAREST,
		GL_LINEAR,
		GL_NEAREST,
	};

	TextureSamplerLibrary TextureSampler::Library = TextureSamplerLibrary();

	std::shared_ptr<TextureSampler> TextureSampler::GetDefault()
	{
		static std::shared_ptr<TextureSampler> sampler = Library.Get({ TextureWrapMode::Repeat, TextureFilterMode::Linear });
		return sampler;
	}

	const TextureSamplerLibrary::TextureSamplerPtr& TextureSamplerLibrary::Get(const TextureSamplerSettings& settings)
	{
		if (auto it = _samplers.find(settings); it != _samplers.end())
		{
			return it->second;
		}
		else
		{
			return _samplers.emplace(settings, std::make_shared<TextureSampler>(settings)).first->second;
		}
	}

	TextureSampler::TextureSampler(const TextureSamplerSettings& settings) :
		_handle(0)
	{
		glGenSamplers(1, &_handle);
		glSamplerParameteri(_handle, GL_TEXTURE_MIN_FILTER, FilterModesMin[static_cast<int>(settings.filter)]);
		glSamplerParameteri(_handle, GL_TEXTURE_MAG_FILTER, FilterModesMag[static_cast<int>(settings.filter)]);
		glSamplerParameteri(_handle, GL_TEXTURE_WRAP_S, WrapModes[static_cast<int>(settings.wrap)]);
		glSamplerParameteri(_handle, GL_TEXTURE_WRAP_T, WrapModes[static_cast<int>(settings.wrap)]);
		glSamplerParameterf(_handle, GL_TEXTURE_MAX_ANISOTROPY, 16);
	}

	TextureSampler::~TextureSampler()
	{
		if (_handle != 0)
		{
			glDeleteSamplers(1, &_handle);
		}
	}

	void TextureSampler::Bind(GLuint unit)
	{
		glBindSampler(unit, _handle);
	}
}
