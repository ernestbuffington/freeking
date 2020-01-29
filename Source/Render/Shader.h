#pragma once

#include "Vector.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "AssetLibrary.h"
#include <glad/glad.h>
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

		void Bind();
		void Unbind();

		void SetUniformValue(const char*, int);
		void SetUniformValue(const char*, float);
		void SetUniformValue(const char*, const Vector2f&);
		void SetUniformValue(const char*, const Vector3f&);
		void SetUniformValue(const char*, const Vector4f&);
		void SetUniformValue(const char*, const Matrix3x3&);
		void SetUniformValue(const char*, const Matrix4x4&);

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
