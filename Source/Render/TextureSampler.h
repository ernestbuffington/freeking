#pragma once

#include <glad/glad.h>

namespace Freeking
{
	enum class WrapMode : int
	{
		WRAPMODE_REPEAT,
		WRAPMODE_CLAMP_EDGE,
	};

	enum class FilterMode : int
	{
		FILTERMODE_LINEAR,
		FILTERMODE_NEAREST,
		FILTERMODE_LINEAR_NO_MIP,
	};

	class TextureSampler
	{
	public:

		TextureSampler(WrapMode wrapMode, FilterMode filterMode);
		~TextureSampler();

		void Bind(GLuint unit);

	private:

		GLuint _handle;
	};
}
