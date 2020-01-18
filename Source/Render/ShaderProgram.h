#pragma once

#include "Vector.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include <glad/glad.h>
#include <map>
#include <string>

namespace Freeking
{
	class ShaderProgram
	{
	public:

		ShaderProgram() = delete;
		ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
		~ShaderProgram();

		void Bind();
		void Unbind();

		void SetUniformValue(const char* uniformName, int value);
		void SetUniformValue(const char* uniformName, float value);
		void SetUniformValue(const char* uniformName, const Vector2f& v);
		void SetUniformValue(const char* uniformName, const Vector3f& v);
		void SetUniformValue(const char* uniformName, const Vector4f& v);
		void SetUniformValue(const char* uniformName, const Matrix3x3& m);
		void SetUniformValue(const char* uniformName, const Matrix4x4& m);
		void SetUniformValue(const char* uniformName, std::size_t count, const Matrix4x4* m);

		GLuint GetRawHandle() const { return _program; }

	private:

		GLuint _program;
		std::map<std::string, GLint> _uniforms;

		GLuint CreateSubShader(GLenum type, const std::string& source);
	};

}
