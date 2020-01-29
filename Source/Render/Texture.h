#pragma once

#include <glad/glad.h>

namespace Freeking
{
	class Texture
	{
	public:

		Texture() = default;
		virtual ~Texture() = default;

		virtual const GLuint GetHandle() const = 0;
	};
}
