#include "TextureSampler.h"

namespace Freeking
{
	static int WrapModes[2] =
	{
		GL_REPEAT,
		GL_CLAMP_TO_EDGE,
	};

	static int FilterModesMin[3] =
	{
		GL_LINEAR_MIPMAP_LINEAR,
		GL_NEAREST_MIPMAP_NEAREST,
		GL_LINEAR,
	};

	static int FilterModesMag[3] =
	{
		GL_LINEAR,
		GL_NEAREST,
		GL_LINEAR,
	};

	TextureSampler::TextureSampler(WrapMode wrapMode, FilterMode filterMode) :
		_handle(0)
	{
		glGenSamplers(1, &_handle);
		glSamplerParameteri(_handle, GL_TEXTURE_MIN_FILTER, FilterModesMin[(int)filterMode]);
		glSamplerParameteri(_handle, GL_TEXTURE_MAG_FILTER, FilterModesMag[(int)filterMode]);
		glSamplerParameteri(_handle, GL_TEXTURE_WRAP_S, WrapModes[(int)wrapMode]);
		glSamplerParameteri(_handle, GL_TEXTURE_WRAP_T, WrapModes[(int)wrapMode]);
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
