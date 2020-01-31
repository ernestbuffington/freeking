#pragma once

#include "Vector.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "AssetLibrary.h"
#include <glad/gl.h>
#include <map>
#include <string>

namespace Freeking
{
	class Shader;

	class ShaderLibrary : public AssetLibrary<Shader>
	{
	protected:

		virtual void UpdateLoaders() override;
	};

	class Shader
	{
	public:

		static ShaderLibrary Library;

		Shader() = delete;
		Shader(const std::string&);
		~Shader();

	private:

		static GLuint CreateSubShader(GLenum, const std::string&, const std::string&);

		struct Uniform
		{
			std::string name;
			GLint location;
			GLenum type;
			int count;
		};

		GLuint _program;
		std::map<std::string, Uniform> _uniforms;

		friend class Material;
	};
}
