#pragma once

#include <glad/gl.h>

namespace Freeking
{
	class Texture
	{
	public:

		Texture() = default;
		virtual ~Texture() = default;

		virtual const GLuint GetId() const = 0;
	};
}
