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

	Shader::Shader(const std::string& source)
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

	Shader::~Shader()
	{
		if (_program)
		{
			glDeleteProgram(_program);
		}
	}

	void Shader::InitializeParameter(const std::string& name, GLint location, GLenum glType)
	{
		if (auto type = FloatParameter::Property::CastType(glType);
			type != FloatParameter::Property::Type::Invalid)
		{
			auto& p = _floatParameters.AddParameter(name);
			p.prop.type = type;
			p.location = location;
			p.prop.unset = true;
			p.prop.dirty = false;

			return;
		}

		if (auto type = IntParameter::Property::CastType(glType);
			type != IntParameter::Property::Type::Invalid)
		{
			auto& p = _intParameters.AddParameter(name);
			p.prop.type = type;
			p.location = location;
			p.prop.unset = true;
			p.prop.dirty = false;

			return;
		}

		if (auto type = MatrixParameter::Property::CastType(glType);
			type != MatrixParameter::Property::Type::Invalid)
		{
			auto& p = _matrixParameters.AddParameter(name);
			p.prop.type = type;
			p.location = location;
			p.prop.unset = true;
			p.prop.dirty = false;

			return;
		}

		if (auto type = TextureParameter::Property::CastType(glType);
			type != TextureParameter::Property::Type::Invalid)
		{
			auto& p = _textureParameters.AddParameter(name);
			p.prop.type = type;
			p.prop.targetType = TextureParameter::Property::CastTargetType(type);
			p.location = location;
			p.prop.unset = true;
			p.unit = static_cast<int>(_textureParameters.GetCount()) - 1;

			// This can be set here as it doesn't change
			glUniform1i(p.location, p.unit);

			return;
		}
	}

	void Shader::Apply()
	{
		if (_program != _activeProgramId)
		{
			glUseProgram(_program);
			_activeProgramId = _program;
		}

		ApplyFloatParameters();
		ApplyIntParameters();
		ApplyMatrixParameters();
		ApplyTextureParameters();
	}

	void Shader::Unbind()
	{
		if (_activeProgramId != 0)
		{
			glUseProgram(0);
			_activeProgramId = 0;
		}
	}

	void Shader::ApplyFloatParameters()
	{
		using Property = FloatParameter::Property;
		using PropertyType = Property::Type;

		for (auto& p : _floatParameters._parameters)
		{
			if (p.prop.unset || !p.prop.dirty)
			{
				continue;
			}

			auto& prop = p.prop;

			switch (prop.type)
			{
			case PropertyType::Float:
			{
				glUniform1f(p.location, prop.value[0]);
				break;
			}
			case PropertyType::Vec2:
			{
				glUniform2f(p.location, prop.value[0], prop.value[1]);
				break;
			}
			case PropertyType::Vec3:
			{
				glUniform3f(p.location, prop.value[0], prop.value[1], prop.value[2]);
				break;
			}
			case PropertyType::Vec4:
			{
				glUniform4f(p.location, prop.value[0], prop.value[1], prop.value[2], prop.value[3]);
				break;
			}
			}

			prop.dirty = false;
		}
	}

	void Shader::ApplyIntParameters()
	{
		using Property = IntParameter::Property;
		using PropertyType = Property::Type;

		for (auto& p : _intParameters._parameters)
		{
			if (p.prop.unset || !p.prop.dirty)
			{
				continue;
			}

			auto& prop = p.prop;

			switch (prop.type)
			{
			case PropertyType::Int:
			{
				glUniform1i(p.location, prop.value[0]);
				break;
			}
			case PropertyType::Vec2:
			{
				glUniform2i(p.location, prop.value[0], prop.value[1]);
				break;
			}
			case PropertyType::Vec3:
			{
				glUniform3i(p.location, prop.value[0], prop.value[1], prop.value[2]);
				break;
			}
			case PropertyType::Vec4:
			{
				glUniform4i(p.location, prop.value[0], prop.value[1], prop.value[2], prop.value[3]);
				break;
			}
			}

			prop.dirty = false;
		}
	}

	void Shader::ApplyMatrixParameters()
	{
		using Property = MatrixParameter::Property;
		using PropertyType = Property::Type;

		for (auto& p : _matrixParameters._parameters)
		{
			if (p.prop.unset || !p.prop.dirty)
			{
				continue;
			}

			auto& prop = p.prop;

			switch (prop.type)
			{
			case PropertyType::Mat3:
			{
				glUniformMatrix3fv(p.location, 1, GL_FALSE, &prop.value[0]);
				break;
			}
			case PropertyType::Mat4:
			{
				glUniformMatrix4fv(p.location, 1, GL_FALSE, &prop.value[0]);
				break;
			}
			}

			prop.dirty = false;
		}
	}

	void Shader::ApplyTextureParameters()
	{
		using Property = TextureParameter::Property;
		using PropertyType = Property::Type;

		for (const auto& p : _textureParameters._parameters)
		{
			if (p.prop.unset)
			{
				continue;
			}

			const auto& prop = p.prop;

			if (prop.targetType != GL_INVALID_ENUM)
			{
				auto& textureBindingState = _textureBindingStates.at(p.unit);
				auto samplerId = prop.samplerId != GL_INVALID_INDEX ? prop.samplerId : 0;

				if (textureBindingState.samplerId != samplerId)
				{
					glBindSampler(p.unit, samplerId);
					textureBindingState.samplerId = samplerId;
				}

				if (textureBindingState.textureId != prop.textureId)
				{
					glActiveTexture(GL_TEXTURE0 + p.unit);
					glBindTexture(prop.targetType, prop.textureId);
					textureBindingState.textureId = prop.textureId;
				}
			}
		}
	}

	void Shader::SetParameterValue(const char* name, int value)
	{
		SetParameterValue(_intParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, int value)
	{
		if (auto param = _intParameters.GetParameter(id);
			param != nullptr && param->prop.type == IntPropertyType::Int)
		{
			param->prop.SetInt(value);
		}
	}

	void Shader::SetParameterValue(const char* name, float value)
	{
		SetParameterValue(_floatParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, float value)
	{
		if (auto param = _floatParameters.GetParameter(id);
			param != nullptr && param->prop.type == FloatPropertyType::Float)
		{
			param->prop.SetFloat(value);
		}
	}

	void Shader::SetParameterValue(const char* name, const Vector2f& value)
	{
		SetParameterValue(_floatParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, const Vector2f& value)
	{
		if (auto param = _floatParameters.GetParameter(id);
			param != nullptr && param->prop.type == FloatPropertyType::Vec2)
		{
			param->prop.SetVec2(value);
		}
	}

	void Shader::SetParameterValue(const char* name, const Vector3f& value)
	{
		SetParameterValue(_floatParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, const Vector3f& value)
	{
		if (auto param = _floatParameters.GetParameter(id);
			param != nullptr && param->prop.type == FloatPropertyType::Vec3)
		{
			param->prop.SetVec3(value);
		}
	}

	void Shader::SetParameterValue(const char* name, const Vector4f& value)
	{
		SetParameterValue(_floatParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, const Vector4f& value)
	{
		if (auto param = _floatParameters.GetParameter(id);
			param != nullptr && param->prop.type == FloatPropertyType::Vec4)
		{
			param->prop.SetVec4(value);
		}
	}

	void Shader::SetParameterValue(const char* name, const Matrix3x3& value)
	{
		SetParameterValue(_matrixParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, const Matrix3x3& value)
	{
		if (auto param = _matrixParameters.GetParameter(id);
			param != nullptr && param->prop.type == MatrixPropertyType::Mat3)
		{
			param->prop.SetMat3(value);
		}
	}

	void Shader::SetParameterValue(const char* name, const Matrix4x4& value)
	{
		SetParameterValue(_matrixParameters.GetId(name), value);
	}

	void Shader::SetParameterValue(int id, const Matrix4x4& value)
	{
		if (auto param = _matrixParameters.GetParameter(id);
			param != nullptr && param->prop.type == MatrixPropertyType::Mat4)
		{
			param->prop.SetMat4(value);
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
		if (!texture)
		{
			return;
		}

		if (auto param = _textureParameters.GetParameter(id);
			param != nullptr && param->prop.type == TexturePropertyType::Tex2D)
		{
			param->prop.SetTexture(texture, sampler);
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
		if (!texture)
		{
			return;
		}

		if (auto param = _textureParameters.GetParameter(id);
			param != nullptr && param->prop.type == TexturePropertyType::TexBuffer)
		{
			param->prop.SetTexture(texture);
		}
	}

	void Shader::SetParameterValue(int id, const TextureCube* texture, const TextureSampler* sampler)
	{
		if (!texture)
		{
			return;
		}

		if (auto param = _textureParameters.GetParameter(id);
			param != nullptr && param->prop.type == TexturePropertyType::TexCube)
		{
			param->prop.SetTexture(texture, sampler);
		}
	}

	void Shader::FloatParameter::Property::SetFloat(float v)
	{
		if (type != Type::Float)
		{
			return;
		}

		if (unset || value[0] != v)
		{
			value[0] = v;
			unset = false;
			dirty = true;
		}
	}

	void Shader::FloatParameter::Property::SetVec2(const Vector2f& v)
	{
		if (type != Type::Vec2)
		{
			return;
		}

		if (unset || (value[0] != v.x || value[1] != v.y))
		{
			std::memcpy(&value[0], v.Base(), 8);
			unset = false;
			dirty = true;
		}
	}

	void Shader::FloatParameter::Property::SetVec3(const Vector3f& v)
	{
		if (type != Type::Vec3)
		{
			return;
		}

		if (unset || (value[0] != v.x || value[1] != v.y || value[2] != v.z))
		{
			std::memcpy(&value[0], v.Base(), 12);
			unset = false;
			dirty = true;
		}
	}

	void Shader::FloatParameter::Property::SetVec4(const Vector4f& v)
	{
		if (type != Type::Vec4)
		{
			return;
		}

		if (unset || (value[0] != v.x || value[1] != v.y || value[2] != v.z || value[3] != v.w))
		{
			std::memcpy(&value[0], v.Base(), 16);
			unset = false;
			dirty = true;
		}
	}

	void Shader::IntParameter::Property::SetInt(int v)
	{
		if (type != Type::Int)
		{
			return;
		}

		if (unset || value[0] != v)
		{
			value[0] = v;
			unset = false;
			dirty = true;
		}
	}

	void Shader::MatrixParameter::Property::SetMat3(const Matrix3x3& v)
	{
		if (type != Type::Mat3)
		{
			return;
		}

		std::memcpy(&value[0], v.Base(), 36);
		unset = false;
		dirty = true;
	}

	void Shader::MatrixParameter::Property::SetMat4(const Matrix4x4& v)
	{
		if (type != Type::Mat4)
		{
			return;
		}

		std::memcpy(&value[0], v.Base(), 64);
		unset = false;
		dirty = true;
	}

	void Shader::TextureParameter::Property::SetTexture(const Texture2D* texture, const TextureSampler* sampler)
	{
		if (type == Type::Tex2D && texture)
		{
			textureId = texture->GetId();
			samplerId = sampler != nullptr ? sampler->GetId() : TextureSampler::GetDefault()->GetId();
			unset = false;
		}
	}

	void Shader::TextureParameter::Property::SetTexture(const TextureBuffer* texture)
	{
		if (type == Type::TexBuffer && texture)
		{
			textureId = texture->GetId();
			samplerId = GL_INVALID_INDEX;
			unset = false;
		}
	}

	void Shader::TextureParameter::Property::SetTexture(const TextureCube* texture, const TextureSampler* sampler)
	{
		if (type == Type::TexCube && texture)
		{
			textureId = texture->GetId();
			samplerId = sampler != nullptr ? sampler->GetId() : TextureSampler::GetDefault()->GetId();
			unset = false;
		}
	}
}
