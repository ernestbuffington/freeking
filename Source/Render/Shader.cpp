#include "Shader.h"
#include "Texture2D.h"
#include "TextureBuffer.h"
#include "TextureCube.h"
#include "TextureSampler.h"
#include "ShaderLoader.h"
#include <cassert>

namespace Freeking
{
	void ShaderLibrary::Initialize()
	{
		DebugLine = Get("Shaders/DebugLine.shader");
		DynamicModel = Get("Shaders/DynamicModel.shader");
		Lightmapped = Get("Shaders/Lightmapped.shader");
		Sprite = Get("Shaders/Sprite.shader");
		Text = Get("Shaders/Text.shader");
		Skybox = Get("Shaders/Skybox.shader");
		Billboard = Get("Shaders/Billboard.shader");
	}

	void ShaderLibrary::UpdateLoaders()
	{
		AddLoader<ShaderLoader>();
	}

	ShaderLibrary Shader::Library;
	GlobalUniformBuffer Shader::GlobalUniforms;

	std::vector<Shader::TextureBindingState> Shader::_textureBindingStates;
	GLuint Shader::_activeProgramId = 0;

	void Shader::Initialize()
	{
		GLint maxCombinedTextureImageUnits;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureImageUnits);
		_textureBindingStates.resize(maxCombinedTextureImageUnits);

		GlobalUniforms.Initialize();
		Library.Initialize();
	}

	Shader::Shader() :
		_program(0)
	{
	}

	Shader::~Shader()
	{
		Unbind();

		if (_program)
		{
			glDeleteProgram(_program);
		}
	}

	void Shader::InitializeParameter(const std::string& name, GLint location, GLenum glType)
	{
		if (auto type = FloatParameter::CastType(glType);
			type != FloatParameter::Type::Invalid)
		{
			auto& p = _floatParameters.AddParameter(name);
			p.type = type;
			p.location = location;
			p.unset = true;

			return;
		}

		if (auto type = IntParameter::CastType(glType);
			type != IntParameter::Type::Invalid)
		{
			auto& p = _intParameters.AddParameter(name);
			p.type = type;
			p.location = location;
			p.unset = true;

			return;
		}

		if (auto type = MatrixParameter::CastType(glType);
			type != MatrixParameter::Type::Invalid)
		{
			auto& p = _matrixParameters.AddParameter(name);
			p.type = type;
			p.location = location;
			p.unset = true;

			return;
		}

		if (auto type = TextureParameter::CastType(glType);
			type != TextureParameter::Type::Invalid)
		{
			auto& p = _textureParameters.AddParameter(name);
			p.type = type;
			p.targetType = TextureParameter::CastTargetType(type);
			p.location = location;
			p.unset = true;
			p.unit = static_cast<int>(_textureParameters.GetCount()) - 1;

			// This can be set here as it doesn't change
			glUniform1i(p.location, p.unit);

			return;
		}
	}

	void Shader::Bind()
	{
		assert(_program != 0);

		if (_program != _activeProgramId)
		{
			glUseProgram(_program);
			_activeProgramId = _program;
		}
	}

	void Shader::Unbind()
	{
		if (_activeProgramId != 0)
		{
			glUseProgram(0);
			_activeProgramId = 0;
		}
	}

	void Shader::SetParameterValue(const char* name, int value)
	{
		SetParameterValue(_intParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, int value)
	{
		assert(_program == _activeProgramId);

		if (auto param = _intParameters.GetParameter(id);
			param != nullptr && param->type == IntParameter::Type::Int)
		{
			param->SetInt(value);
		}
	}

	void Shader::SetParameterValue(const char* name, float value)
	{
		SetParameterValue(_floatParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, float value)
	{
		assert(_program == _activeProgramId);

		if (auto param = _floatParameters.GetParameter(id);
			param != nullptr && param->type == FloatParameter::Type::Float)
		{
			param->SetFloat(value);
		}
	}

	void Shader::SetParameterValue(const char* name, const Vector2f& value)
	{
		SetParameterValue(_floatParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, const Vector2f& value)
	{
		assert(_program == _activeProgramId);

		if (auto param = _floatParameters.GetParameter(id);
			param != nullptr && param->type == FloatParameter::Type::Vec2)
		{
			param->SetVec2(value);
		}
	}

	void Shader::SetParameterValue(const char* name, const Vector3f& value)
	{
		SetParameterValue(_floatParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, const Vector3f& value)
	{
		assert(_program == _activeProgramId);

		if (auto param = _floatParameters.GetParameter(id);
			param != nullptr && param->type == FloatParameter::Type::Vec3)
		{
			param->SetVec3(value);
		}
	}

	void Shader::SetParameterValue(const char* name, const Vector4f& value)
	{
		SetParameterValue(_floatParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, const Vector4f& value)
	{
		assert(_program == _activeProgramId);

		if (auto param = _floatParameters.GetParameter(id);
			param != nullptr && param->type == FloatParameter::Type::Vec4)
		{
			param->SetVec4(value);
		}
	}

	void Shader::SetParameterValue(const char* name, const Matrix3x3& value)
	{
		SetParameterValue(_matrixParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, const Matrix3x3& value)
	{
		assert(_program == _activeProgramId);

		if (auto param = _matrixParameters.GetParameter(id);
			param != nullptr && param->type == MatrixParameter::Type::Mat3)
		{
			param->SetMat3(value);
		}
	}

	void Shader::SetParameterValue(const char* name, const Matrix4x4& value)
	{
		SetParameterValue(_matrixParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, const Matrix4x4& value)
	{
		assert(_program == _activeProgramId);

		if (auto param = _matrixParameters.GetParameter(id);
			param != nullptr && param->type == MatrixParameter::Type::Mat4)
		{
			param->SetMat4(value);
		}
	}

	void Shader::SetParameterValue(const char* name, const Texture2D* value)
	{
		SetParameterValue(name, value, TextureSampler::GetDefault().get());
	}

	void Shader::SetParameterValue(int id, const Texture2D* value)
	{
		SetParameterValue(id, value, TextureSampler::GetDefault().get());
	}

	void Shader::SetParameterValue(const char* name, const Texture2D* texture, const TextureSampler* sampler)
	{
		if (!texture)
		{
			return;
		}

		SetParameterValue(_textureParameters.GetId(name), texture, sampler);
	}

	void Shader::SetParameterValue(int id, const Texture2D* texture, const TextureSampler* sampler)
	{
		assert(_program == _activeProgramId);

		if (!texture)
		{
			return;
		}

		if (auto param = _textureParameters.GetParameter(id);
			param != nullptr && param->type == TextureParameter::Type::Tex2D)
		{
			param->SetTexture(texture, sampler);
		}
	}

	void Shader::SetParameterValue(const char* name, const TextureBuffer* texture)
	{
		if (!texture)
		{
			return;
		}

		SetParameterValue(_textureParameters.GetId(name), texture);
	}

	void Shader::SetParameterValue(const char* name, const TextureCube* texture, const TextureSampler* sampler)
	{
		if (!texture)
		{
			return;
		}

		SetParameterValue(_textureParameters.GetId(name), texture, sampler);
	}

	void Shader::SetParameterValue(int id, const TextureBuffer* texture)
	{
		assert(_program == _activeProgramId);

		if (!texture)
		{
			return;
		}

		if (auto param = _textureParameters.GetParameter(id);
			param != nullptr && param->type == TextureParameter::Type::TexBuffer)
		{
			param->SetTexture(texture);
		}
	}

	void Shader::SetParameterValue(int id, const TextureCube* texture, const TextureSampler* sampler)
	{
		assert(_program == _activeProgramId);

		if (!texture)
		{
			return;
		}

		if (auto param = _textureParameters.GetParameter(id);
			param != nullptr && param->type == TextureParameter::Type::TexCube)
		{
			param->SetTexture(texture, sampler);
		}
	}

	void Shader::FloatParameter::SetFloat(float v)
	{
		if (type != Type::Float)
		{
			return;
		}

		if (unset || value[0] != v)
		{
			value[0] = v;
			unset = false;

			glUniform1f(location, value[0]);
		}
	}

	void Shader::FloatParameter::SetVec2(const Vector2f& v)
	{
		if (type != Type::Vec2)
		{
			return;
		}

		if (unset || (value[0] != v.x || value[1] != v.y))
		{
			std::memcpy(&value[0], v.Base(), 8);
			unset = false;

			glUniform2f(location, value[0], value[1]);
		}
	}

	void Shader::FloatParameter::SetVec3(const Vector3f& v)
	{
		if (type != Type::Vec3)
		{
			return;
		}

		if (unset || (value[0] != v.x || value[1] != v.y || value[2] != v.z))
		{
			std::memcpy(&value[0], v.Base(), 12);
			unset = false;

			glUniform3f(location, value[0], value[1], value[2]);
		}
	}

	void Shader::FloatParameter::SetVec4(const Vector4f& v)
	{
		if (type != Type::Vec4)
		{
			return;
		}

		if (unset || (value[0] != v.x || value[1] != v.y || value[2] != v.z || value[3] != v.w))
		{
			std::memcpy(&value[0], v.Base(), 16);
			unset = false;

			glUniform4f(location, value[0], value[1], value[2], value[3]);
		}
	}

	void Shader::IntParameter::SetInt(int v)
	{
		if (type != Type::Int)
		{
			return;
		}

		if (unset || value[0] != v)
		{
			value[0] = v;
			unset = false;

			glUniform1i(location, value[0]);
		}
	}

	void Shader::MatrixParameter::SetMat3(const Matrix3x3& v)
	{
		if (type != Type::Mat3)
		{
			return;
		}

		std::memcpy(&value[0], v.Base(), 36);
		unset = false;

		glUniformMatrix3fv(location, 1, GL_FALSE, &value[0]);
	}

	void Shader::MatrixParameter::SetMat4(const Matrix4x4& v)
	{
		if (type != Type::Mat4)
		{
			return;
		}

		std::memcpy(&value[0], v.Base(), 64);
		unset = false;

		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0]);
	}

	void Shader::TextureParameter::SetTexture(const Texture2D* texture, const TextureSampler* sampler)
	{
		if (type == Type::Tex2D && texture)
		{
			textureId = texture->GetId();
			samplerId = sampler != nullptr ? sampler->GetId() : TextureSampler::GetDefault()->GetId();
			unset = false;

			Apply();
		}
	}

	void Shader::TextureParameter::SetTexture(const TextureBuffer* texture)
	{
		if (type == Type::TexBuffer && texture)
		{
			textureId = texture->GetId();
			samplerId = GL_INVALID_INDEX;
			unset = false;

			Apply();
		}
	}

	void Shader::TextureParameter::SetTexture(const TextureCube* texture, const TextureSampler* sampler)
	{
		if (type == Type::TexCube && texture)
		{
			textureId = texture->GetId();
			samplerId = sampler != nullptr ? sampler->GetId() : TextureSampler::GetDefault()->GetId();
			unset = false;

			Apply();
		}
	}

	void Shader::TextureParameter::Apply()
	{
		if (targetType != GL_INVALID_ENUM)
		{
			auto& textureBindingState = _textureBindingStates.at(unit);
			auto newSamplerId = samplerId != GL_INVALID_INDEX ? samplerId : 0;

			if (textureBindingState.samplerId != newSamplerId)
			{
				glBindSampler(unit, newSamplerId);
				textureBindingState.samplerId = newSamplerId;
			}

			if (textureBindingState.textureId != textureId)
			{
				glActiveTexture(GL_TEXTURE0 + unit);
				glBindTexture(targetType, textureId);
				textureBindingState.textureId = textureId;
			}
		}
	}

	static GLuint CreateSubShader(GLenum type, const std::string& source, const std::string& defines)
	{
		GLuint shader = glCreateShader(type);

		static const std::string version("#version 460\n");
		const GLchar* sources[] = { version.c_str(), defines.c_str(), source.c_str() };
		const GLint lengths[] = { (GLint)version.size(), (GLint)defines.size(), (GLint)source.size() };
		glShaderSource(shader, 3, sources, lengths);
		glCompileShader(shader);

		GLint compileStatus = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

		if (compileStatus == GL_FALSE)
		{
			GLint infoLogLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

			char* infoLog = new char[infoLogLen];
			glGetShaderInfoLog(shader, infoLogLen, &infoLogLen, infoLog);
			std::fprintf(stderr, "Shader compile errors:\n%s\n", infoLog);
			delete[] infoLog;

			glDeleteShader(shader);

			return 0;
		}

		return shader;
	}

	void Shader::Compile(const std::string& source)
	{
		_program = glCreateProgram();

		assert(_program != 0);

		GLuint vertexShader = CreateSubShader(GL_VERTEX_SHADER, source.c_str(), "#define VERTEX\n");
		GLuint fragmentShader = CreateSubShader(GL_FRAGMENT_SHADER, source.c_str(), "#define FRAGMENT\n");

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
			std::fprintf(stderr, "Shader linking errors:\n%s\n", infoLog);
			delete[] infoLog;

			glDeleteProgram(_program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			_program = 0;

			return;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		int uniformBlockCount = -1;
		glGetProgramiv(_program, GL_ACTIVE_UNIFORM_BLOCKS, &uniformBlockCount);
		for (int i = 0; i < uniformBlockCount; i++)
		{
			int length​ = -1;
			char uniformBlockName​[64];
			glGetActiveUniformBlockName(_program, GLuint(i), sizeof(uniformBlockName​) - 1, &length​, uniformBlockName​);
			uniformBlockName​[length​] = 0;
			auto nameString = std::string(uniformBlockName​);

			if (nameString == "GlobalUniforms")
			{
				glUniformBlockBinding(_program, i, 0);
			}
		}

		GLint currentProgramId;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgramId);
		glUseProgram(_program);

		int uniformCount = -1;
		glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &uniformCount);
		for (int i = 0; i < uniformCount; i++)
		{
			int name_len = -1;
			int num = -1;
			GLenum type = GL_ZERO;
			char name[64];
			glGetActiveUniform(_program, GLuint(i), sizeof(name) - 1, &name_len, &num, &type, name);
			name[name_len] = 0;
			auto nameString = std::string(name);

			if (auto location = glGetUniformLocation(_program, name);
				location != -1)
			{
				InitializeParameter(nameString, location, type);
			}
		}

		glUseProgram(currentProgramId);
	}

	GlobalUniformBuffer::GlobalUniformBuffer() :
		_bufferId(0)
	{
	}

	GlobalUniformBuffer::~GlobalUniformBuffer()
	{
		if (_bufferId)
		{
			glDeleteBuffers(1, &_bufferId);
		}
	}

	void GlobalUniformBuffer::Initialize()
	{
		if (_bufferId)
		{
			return;
		}

		glGenBuffers(1, &_bufferId);
		glBindBuffer(GL_UNIFORM_BUFFER, _bufferId);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(UniformBlock), NULL, GL_STATIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _bufferId);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void GlobalUniformBuffer::Update()
	{
		if (!_bufferId)
		{
			return;
		}

		glBindBuffer(GL_UNIFORM_BUFFER, _bufferId);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(UniformBlock), &Uniforms);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}
