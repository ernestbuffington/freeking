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
	Shader::PropertyGlobals Shader::Globals;

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

			return;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

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

			InitializeParameter(nameString, glGetUniformLocation(_program, name), type);
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
			p.globalId = Globals.AddFloatProperty(name, type);

			return;
		}

		if (auto type = IntParameter::Property::CastType(glType);
			type != IntParameter::Property::Type::Invalid)
		{
			auto& p = _intParameters.AddParameter(name);
			p.prop.type = type;
			p.location = location;
			p.prop.unset = true;
			p.globalId = Globals.AddIntProperty(name, type);

			return;
		}

		if (auto type = MatrixParameter::Property::CastType(glType);
			type != MatrixParameter::Property::Type::Invalid)
		{
			auto& p = _matrixParameters.AddParameter(name);
			p.prop.type = type;
			p.location = location;
			p.prop.unset = true;
			p.globalId = Globals.AddMatrixProperty(name, type);

			return;
		}

		if (auto type = TextureParameter::Property::CastType(glType);
			type != TextureParameter::Property::Type::Invalid)
		{
			auto& p = _textureParameters.AddParameter(name);
			p.prop.type = type;
			p.location = location;
			p.prop.unset = true;
			p.globalId = Globals.AddTextureProperty(name, type);
			p.unit = static_cast<int>(_textureParameters.GetCount()) - 1;

			return;
		}
	}

	void Shader::Apply()
	{
		glUseProgram(_program);

		ApplyFloatParameters();
		ApplyIntParameters();
		ApplyMatrixParameters();
		ApplyTextureParameters();
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		for (auto i = 0; i < _textureParameters.GetCount(); ++i)
		{
			glBindSampler(i, 0);
		}
	}

	void Shader::ApplyFloatParameters()
	{
		using Property = FloatParameter::Property;
		using PropertyType = Property::Type;

		for (auto p : _floatParameters._parameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (prop = Globals.GetFloatProperty(p.globalId);
					prop == nullptr ||
					prop->unset ||
					prop->type != p.prop.type)
				{
					continue;
				}
			}
			else
			{
				prop = &p.prop;
			}

			switch (prop->type)
			{
			case PropertyType::Float:
			{
				glUniform1f(p.location, prop->value[0]);
				break;
			}
			case PropertyType::Vec2:
			{
				glUniform2f(p.location, prop->value[0], prop->value[1]);
				break;
			}
			case PropertyType::Vec3:
			{
				glUniform3f(p.location, prop->value[0], prop->value[1], prop->value[2]);
				break;
			}
			case PropertyType::Vec4:
			{
				glUniform4f(p.location, prop->value[0], prop->value[1], prop->value[2], prop->value[3]);
				break;
			}
			}
		}
	}

	void Shader::ApplyIntParameters()
	{
		using Property = IntParameter::Property;
		using PropertyType = Property::Type;

		for (auto p : _intParameters._parameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (prop = Globals.GetIntProperty(p.globalId);
					prop == nullptr ||
					prop->unset ||
					prop->type != p.prop.type)
				{
					continue;
				}
			}
			else
			{
				prop = &p.prop;
			}

			switch (prop->type)
			{
			case PropertyType::Int:
			{
				glUniform1i(p.location, prop->value[0]);
				break;
			}
			case PropertyType::Vec2:
			{
				glUniform2i(p.location, prop->value[0], prop->value[1]);
				break;
			}
			case PropertyType::Vec3:
			{
				glUniform3i(p.location, prop->value[0], prop->value[1], prop->value[2]);
				break;
			}
			case PropertyType::Vec4:
			{
				glUniform4i(p.location, prop->value[0], prop->value[1], prop->value[2], prop->value[3]);
				break;
			}
			}
		}
	}

	void Shader::ApplyMatrixParameters()
	{
		using Property = MatrixParameter::Property;
		using PropertyType = Property::Type;

		for (auto p : _matrixParameters._parameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (prop = Globals.GetMatrixProperty(p.globalId);
					prop == nullptr ||
					prop->unset ||
					prop->type != p.prop.type)
				{
					continue;
				}
			}
			else
			{
				prop = &p.prop;
			}

			switch (prop->type)
			{
			case PropertyType::Mat3:
			{
				glUniformMatrix3fv(p.location, 1, GL_FALSE, &prop->value[0]);
				break;
			}
			case PropertyType::Mat4:
			{
				glUniformMatrix4fv(p.location, 1, GL_FALSE, &prop->value[0]);
				break;
			}
			}
		}
	}

	void Shader::ApplyTextureParameters()
	{
		using Property = TextureParameter::Property;
		using PropertyType = Property::Type;

		for (auto p : _textureParameters._parameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (prop = Globals.GetTextureProperty(p.globalId);
					prop == nullptr ||
					prop->unset ||
					prop->type != p.prop.type)
				{
					continue;
				}
			}
			else
			{
				prop = &p.prop;
			}

			GLenum textureType = GL_INVALID_ENUM;

			switch (prop->type)
			{
			case PropertyType::Tex1D: textureType = GL_TEXTURE_1D; break;
			case PropertyType::Tex2D: textureType = GL_TEXTURE_2D; break;
			case PropertyType::Tex3D: textureType = GL_TEXTURE_3D; break;
			case PropertyType::TexBuffer: textureType = GL_TEXTURE_BUFFER; break;
			case PropertyType::TexCube: textureType = GL_TEXTURE_CUBE_MAP; break;
			}

			if (textureType != GL_INVALID_ENUM)
			{
				glBindSampler(p.unit, prop->samplerId != GL_INVALID_INDEX ? prop->samplerId : 0);
				glActiveTexture(GL_TEXTURE0 + p.unit);
				glBindTexture(textureType, prop->textureId);
				glUniform1i(p.location, p.unit);
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
		if (type == Type::Float)
		{
			value[0] = v;
			unset = false;
		}
	}

	void Shader::FloatParameter::Property::SetVec2(const Vector2f& v)
	{
		if (type == Type::Vec2)
		{
			std::memcpy(&value[0], v.Base(), 8);
			unset = false;
		}
	}

	void Shader::FloatParameter::Property::SetVec3(const Vector3f& v)
	{
		if (type == Type::Vec3)
		{
			std::memcpy(&value[0], v.Base(), 12);
			unset = false;
		}
	}

	void Shader::FloatParameter::Property::SetVec4(const Vector4f& v)
	{
		if (type == Type::Vec4)
		{
			std::memcpy(&value[0], v.Base(), 16);
			unset = false;
		}
	}

	void Shader::IntParameter::Property::SetInt(int v)
	{
		if (type == Type::Int)
		{
			value[0] = v;
			unset = false;
		}
	}

	void Shader::MatrixParameter::Property::SetMat3(const Matrix3x3& v)
	{
		if (type == Type::Mat3)
		{
			std::memcpy(&value[0], v.Base(), 36);
			unset = false;
		}
	}

	void Shader::MatrixParameter::Property::SetMat4(const Matrix4x4& v)
	{
		if (type == Type::Mat4)
		{
			std::memcpy(&value[0], v.Base(), 64);
			unset = false;
		}
	}

	void Shader::TextureParameter::Property::SetTexture(const Texture2D* texture, const TextureSampler* sampler)
	{
		if (type == Type::Tex2D && texture)
		{
			textureId = texture->GetHandle();
			samplerId = sampler != nullptr ? sampler->GetHandle() : TextureSampler::GetDefault()->GetHandle();
			unset = false;
		}
	}

	void Shader::TextureParameter::Property::SetTexture(const TextureBuffer* texture)
	{
		if (type == Type::TexBuffer && texture)
		{
			textureId = texture->GetHandle();
			samplerId = GL_INVALID_INDEX;
			unset = false;
		}
	}

	void Shader::TextureParameter::Property::SetTexture(const TextureCube* texture, const TextureSampler* sampler)
	{
		if (type == Type::TexCube && texture)
		{
			textureId = texture->GetHandle();
			samplerId = sampler != nullptr ? sampler->GetHandle() : TextureSampler::GetDefault()->GetHandle();
			unset = false;
		}
	}

	void Shader::PropertyGlobals::SetValue(const char* name, int value)
	{
		SetValue(GetIntId(name), value);
	}

	void Shader::PropertyGlobals::SetValue(int id, int value)
	{
		if (auto p = GetIntProperty(id);
			p != nullptr && p->type == IntPropertyType::Int)
		{
			p->SetInt(value);
		}
	}

	void Shader::PropertyGlobals::SetValue(const char* name, float value)
	{
		SetValue(GetFloatId(name), value);
	}

	void Shader::PropertyGlobals::SetValue(int id, float value)
	{
		if (auto p = GetFloatProperty(id);
			p != nullptr && p->type == FloatPropertyType::Float)
		{
			p->SetFloat(value);
		}
	}

	void Shader::PropertyGlobals::SetValue(const char* name, const Vector2f& value)
	{
		SetValue(GetFloatId(name), value);
	}

	void Shader::PropertyGlobals::SetValue(int id, const Vector2f& value)
	{
		if (auto p = GetFloatProperty(id);
			p != nullptr && p->type == FloatPropertyType::Vec2)
		{
			p->SetVec2(value);
		}
	}

	void Shader::PropertyGlobals::SetValue(const char* name, const Vector3f& value)
	{
		SetValue(GetFloatId(name), value);
	}

	void Shader::PropertyGlobals::SetValue(int id, const Vector3f& value)
	{
		if (auto p = GetFloatProperty(id);
			p != nullptr && p->type == FloatPropertyType::Vec3)
		{
			p->SetVec3(value);
		}
	}

	void Shader::PropertyGlobals::SetValue(const char* name, const Vector4f& value)
	{
		SetValue(GetFloatId(name), value);
	}

	void Shader::PropertyGlobals::SetValue(int id, const Vector4f& value)
	{
		if (auto p = GetFloatProperty(id);
			p != nullptr && p->type == FloatPropertyType::Vec4)
		{
			p->SetVec4(value);
		}
	}

	void Shader::PropertyGlobals::SetValue(const char* name, const Matrix3x3& value)
	{
		SetValue(GetMatrixId(name), value);
	}

	void Shader::PropertyGlobals::SetValue(int id, const Matrix3x3& value)
	{
		if (auto p = GetMatrixProperty(id);
			p != nullptr && p->type == MatrixPropertyType::Mat3)
		{
			p->SetMat3(value);
		}
	}

	void Shader::PropertyGlobals::SetValue(const char* name, const Matrix4x4& value)
	{
		SetValue(GetMatrixId(name), value);
	}

	void Shader::PropertyGlobals::SetValue(int id, const Matrix4x4& value)
	{
		if (auto p = GetMatrixProperty(id);
			p != nullptr && p->type == MatrixPropertyType::Mat4)
		{
			p->SetMat4(value);
		}
	}

	void Shader::PropertyGlobals::SetValue(const char* name, const Texture2D* texture)
	{
		if (texture != nullptr)
		{
			SetValue(name, texture, TextureSampler::GetDefault().get());
		}
	}

	void Shader::PropertyGlobals::SetValue(int id, const Texture2D* texture)
	{
		if (texture != nullptr)
		{
			SetValue(id, texture, TextureSampler::GetDefault().get());
		}
	}

	void Shader::PropertyGlobals::SetValue(const char* name, const Texture2D* texture, const TextureSampler* sampler)
	{
		if (texture == nullptr)
		{
			return;
		}

		SetValue(GetTextureId(name), texture, sampler);
	}

	void Shader::PropertyGlobals::SetValue(int id, const Texture2D* texture, const TextureSampler* sampler)
	{
		if (texture == nullptr)
		{
			return;
		}

		if (auto p = GetTextureProperty(id);
			p != nullptr && p->type == TexturePropertyType::Tex2D)
		{
			p->SetTexture(texture, sampler);
		}
	}

	void Shader::PropertyGlobals::SetValue(const char* name, const TextureBuffer* texture)
	{
		if (texture == nullptr)
		{
			return;
		}

		SetValue(GetTextureId(name), texture);
	}

	void Shader::PropertyGlobals::SetValue(int id, const TextureBuffer* texture)
	{
		if (texture == nullptr)
		{
			return;
		}

		if (auto p = GetTextureProperty(id);
			p != nullptr && p->type == TexturePropertyType::TexBuffer)
		{
			p->SetTexture(texture);
		}
	}
}
