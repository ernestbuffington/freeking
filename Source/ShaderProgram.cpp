#include "ShaderProgram.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace Freeking
{
	ShaderProgram::ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
	{
		_program = glCreateProgram();

		assert(_program != 0);

		GLuint vertexShader = CreateSubShader(GL_VERTEX_SHADER, vertexSource.c_str());
		GLuint fragmentShader = CreateSubShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

		assert(vertexShader != 0 && fragmentShader != 0);

		glAttachShader(_program, vertexShader);
		glAttachShader(_program, fragmentShader);
		glLinkProgram(_program);

		GLint linkStatus = GL_FALSE;
		glGetProgramiv(_program, GL_LINK_STATUS, &linkStatus);

		if (linkStatus == GL_FALSE)
		{
			GLint infoLogLen = 0;
			glGetShaderiv(_program, GL_INFO_LOG_LENGTH, &infoLogLen);

			char* infoLog = new char[infoLogLen];
			glGetProgramInfoLog(_program, infoLogLen, &infoLogLen, infoLog);
			std::fprintf(stderr, "ShaderProgram linking errors:\n%s\n", infoLog);
			delete[] infoLog;

			glDeleteProgram(_program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		int uniformCount = -1;
		glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &uniformCount);
		for (int i = 0; i < uniformCount; i++)
		{
			int name_len = -1, num = -1;
			GLenum type = GL_ZERO;
			char name[64];
			glGetActiveUniform(_program, GLuint(i), sizeof(name) - 1, &name_len, &num, &type, name);
			name[name_len] = 0;

			_uniforms[std::string(name)] = glGetUniformLocation(_program, name);
		}
	}

	ShaderProgram::~ShaderProgram()
	{
		if (_program != 0)
		{
			glDeleteProgram(_program);
		}
	}

	void ShaderProgram::Bind()
	{
		glUseProgram(_program);
	}

	void ShaderProgram::Unbind()
	{
		glUseProgram(0);
	}

	void ShaderProgram::SetUniformValue(const char* uniformName, int value)
	{
		glUniform1i(_uniforms[uniformName], value);
	}

	void ShaderProgram::SetUniformValue(const char* uniformName, float value)
	{
		glUniform1f(_uniforms[uniformName], value);
	}

	void ShaderProgram::SetUniformValue(const char* uniformName, const Vector2f& v)
	{
		glUniform2fv(_uniforms[uniformName], 1, v.Base());
	}

	void ShaderProgram::SetUniformValue(const char* uniformName, const Vector3f& v)
	{
		glUniform3fv(_uniforms[uniformName], 1, v.Base());
	}

	void ShaderProgram::SetUniformValue(const char* uniformName, const Vector4f& v)
	{
		glUniform4fv(_uniforms[uniformName], 1, v.Base());
	}

	void ShaderProgram::SetUniformValue(const char* uniformName, const Matrix3x3& m)
	{
		glUniformMatrix3fv(_uniforms[uniformName], 1, GL_FALSE, m.Base());
	}

	void ShaderProgram::SetUniformValue(const char* uniformName, const Matrix4x4& m)
	{
		glUniformMatrix4fv(_uniforms[uniformName], 1, GL_FALSE, m.Base());
	}

	void ShaderProgram::SetUniformValue(const char* uniformName, std::size_t count, const Matrix4x4* m)
	{
		glUniformMatrix4fv(_uniforms[uniformName], (GLsizei)count, GL_FALSE, m[0].Base());
	}

	GLuint ShaderProgram::CreateSubShader(GLenum type, const std::string& source)
	{
		GLuint shader = glCreateShader(type);

		const GLchar* glsource = (const GLchar*)source.c_str();
		glShaderSource(shader, 1, &glsource, nullptr);
		glCompileShader(shader);

		GLint compileStatus = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

		if (compileStatus == GL_FALSE)
		{
			GLint infoLogLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

			char* infoLog = new char[infoLogLen];
			glGetShaderInfoLog(shader, infoLogLen, &infoLogLen, infoLog);
			std::fprintf(stderr, "ShaderProgram compile errors:\n%s\n", infoLog);
			delete[] infoLog;

			glDeleteShader(shader);

			return 0;
		}

		return shader;
	}
}
