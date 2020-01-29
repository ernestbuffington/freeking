#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureSampler.h"

namespace Freeking
{
	Material::FloatUniformType Material::ToFloatUniformType(GLenum type)
	{
		switch (type)
		{
		case GL_FLOAT: return FloatUniformType::Float;
		case GL_FLOAT_VEC2: return FloatUniformType::Vec2;
		case GL_FLOAT_VEC3: return FloatUniformType::Vec3;
		case GL_FLOAT_VEC4: return FloatUniformType::Vec4;
		}

		return FloatUniformType::Invalid;
	}

	Material::IntUniformType Material::ToIntUniformType(GLenum type)
	{
		switch (type)
		{
		case GL_INT: return IntUniformType::Int;
		case GL_INT_VEC2: return IntUniformType::Vec2;
		case GL_INT_VEC3: return IntUniformType::Vec3;
		case GL_INT_VEC4: return IntUniformType::Vec4;
		}

		return IntUniformType::Invalid;
	}

	Material::MatrixUniformType Material::ToMatrixUniformType(GLenum type)
	{
		switch (type)
		{
		case GL_FLOAT_MAT3: return MatrixUniformType::Mat3;
		case GL_FLOAT_MAT4: return MatrixUniformType::Mat4;
		}

		return MatrixUniformType::Invalid;
	}

	Material::TextureUniformType Material::ToTextureUniformType(GLenum type)
	{
		switch (type)
		{
		case GL_SAMPLER_1D: return TextureUniformType::Tex1D;
		case GL_SAMPLER_2D: return TextureUniformType::Tex2D;
		case GL_SAMPLER_3D: return TextureUniformType::Tex3D;
		case GL_SAMPLER_BUFFER: return TextureUniformType::TexBuffer;
		case GL_INT_SAMPLER_BUFFER: return TextureUniformType::TexBuffer;
		case GL_UNSIGNED_INT_SAMPLER_BUFFER: return TextureUniformType::TexBuffer;
		}

		return TextureUniformType::Invalid;
	}

	Material::Material(std::shared_ptr<Shader> shader) :
		_shader(shader)
	{
		InitializeParameters();
	}

	void Material::InitializeParameters()
	{
		if (!_shader)
		{
			return;
		}

		for (auto& [name, uniform] : _shader->_uniforms)
		{
			if (auto type = ToFloatUniformType(uniform.type); type != FloatUniformType::Invalid)
			{
				FloatParameter p;
				p.location = uniform.location;
				p.type = type;
				p.dirty = false;
				p.unset = true;
				_floatParameters.emplace(uniform.name, p);
			}
			else if (auto type = ToIntUniformType(uniform.type); type != IntUniformType::Invalid)
			{
				IntParameter p;
				p.location = uniform.location;
				p.type = type;
				p.dirty = false;
				p.unset = true;
				_intParameters.emplace(uniform.name, p);
			}
			else if (auto type = ToMatrixUniformType(uniform.type); type != MatrixUniformType::Invalid)
			{
				MatrixParameter p;
				p.location = uniform.location;
				p.type = type;
				p.dirty = false;
				p.unset = true;
				_matrixParameters.emplace(uniform.name, p);
			}
			else if (auto type = ToTextureUniformType(uniform.type); type != TextureUniformType::Invalid)
			{
				TextureParameter p;
				p.location = uniform.location;
				p.type = type;
				p.dirty = false;
				p.unset = true;
				_textureParameters.emplace(uniform.name, p);
			}
		}
	}

	void Material::Apply()
	{
		if (!_shader)
		{
			return;
		}

		glUseProgram(_shader->_program);

		ApplyFloatParameters();
		ApplyIntParameters();
		ApplyMatrixParameters();
		ApplyTextureParameters();
	}

	void Material::Unbind()
	{
		glUseProgram(0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		for (auto i = 0; i < _textureParameters.size(); ++i)
		{
			glBindSampler(i, 0);
		}
	}

	void Material::ApplyFloatParameters()
	{
		for (auto [name, p] : _floatParameters)
		{
			if (!p.dirty || p.unset)
			{
				continue;
			}

			switch (p.type)
			{
			case FloatUniformType::Float:
			{
				glUniform1f(p.location, p.value[0]);
				break;
			}
			case FloatUniformType::Vec2:
			{
				glUniform2f(p.location, p.value[0], p.value[1]);
				break;
			}
			case FloatUniformType::Vec3:
			{
				glUniform3f(p.location, p.value[0], p.value[1], p.value[2]);
				break;
			}
			case FloatUniformType::Vec4:
			{
				glUniform4f(p.location, p.value[0], p.value[1], p.value[2], p.value[3]);
				break;
			}
			}

			p.dirty = false;
		}
	}

	void Material::ApplyIntParameters()
	{
		for (auto [name, p] : _intParameters)
		{
			if (!p.dirty || p.unset)
			{
				continue;
			}

			switch (p.type)
			{
			case IntUniformType::Int:
			{
				glUniform1i(p.location, p.value[0]);
				break;
			}
			case IntUniformType::Vec2:
			{
				glUniform2i(p.location, p.value[0], p.value[1]);
				break;
			}
			case IntUniformType::Vec3:
			{
				glUniform3i(p.location, p.value[0], p.value[1], p.value[2]);
				break;
			}
			case IntUniformType::Vec4:
			{
				glUniform4i(p.location, p.value[0], p.value[1], p.value[2], p.value[3]);
				break;
			}
			}

			p.dirty = false;
		}
	}

	void Material::ApplyMatrixParameters()
	{
		for (auto [name, p] : _matrixParameters)
		{
			if (!p.dirty || p.unset)
			{
				continue;
			}

			switch (p.type)
			{
			case MatrixUniformType::Mat3:
			{
				glUniformMatrix3fv(p.location, 1, GL_FALSE, &p.value[0]);
				break;
			}
			case MatrixUniformType::Mat4:
			{
				glUniformMatrix4fv(p.location, 1, GL_FALSE, &p.value[0]);
				break;
			}
			}

			p.dirty = false;
		}
	}

	void Material::ApplyTextureParameters()
	{
		int textureIndex = -1;

		for (auto [name, p] : _textureParameters)
		{
			textureIndex++;

			if (!p.dirty || p.unset)
			{
				continue;
			}

			GLenum textureType = GL_INVALID_ENUM;

			switch (p.type)
			{
			case TextureUniformType::Tex1D: textureType = GL_TEXTURE_1D; break;
			case TextureUniformType::Tex2D: textureType = GL_TEXTURE_2D; break;
			case TextureUniformType::Tex3D: textureType = GL_TEXTURE_3D; break;
			case TextureUniformType::TexBuffer: textureType = GL_TEXTURE_BUFFER; break;
			}

			if (textureType != GL_INVALID_ENUM)
			{
				glBindSampler(textureIndex, p.sampler);
				glActiveTexture(GL_TEXTURE0 + textureIndex);
				glBindTexture(textureType, p.value);
				glUniform1i(p.location, textureIndex);
			}

			p.dirty = false;
		}
	}

	void Material::SetParameterValue(const char* name, int value)
	{
		if (auto it = _intParameters.find(name); it != _intParameters.end())
		{
			auto& p = it->second;
			if (p.unset || value != p.value[0])
			{
				p.value[0] = value;
				p.unset = false;
				p.dirty = true;
			}
		}
	}

	void Material::SetParameterValue(const char* name, float value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			auto& p = it->second;
			if (p.unset || value != p.value[0])
			{
				p.value[0] = value;
				p.unset = false;
				p.dirty = true;
			}
		}
	}

	void Material::SetParameterValue(const char* name, const Vector2f& value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			auto& p = it->second;
			if (p.unset || std::memcmp(&p.value[0], value.Base(), 8) != 0)
			{
				std::memcpy(&p.value[0], value.Base(), 8);
				p.unset = false;
				p.dirty = true;
			}
		}
	}

	void Material::SetParameterValue(const char* name, const Vector3f& value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			auto& p = it->second;
			if (p.unset || std::memcmp(&p.value[0], value.Base(), 12) != 0)
			{
				std::memcpy(&p.value[0], value.Base(), 12);
				p.unset = false;
				p.dirty = true;
			}
		}
	}

	void Material::SetParameterValue(const char* name, const Vector4f& value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			auto& p = it->second;
			if (p.unset || std::memcmp(&p.value[0], value.Base(), 16) != 0)
			{
				std::memcpy(&p.value[0], value.Base(), 16);
				p.unset = false;
				p.dirty = true;
			}
		}
	}

	void Material::SetParameterValue(const char* name, const Matrix3x3& value)
	{
		if (auto it = _matrixParameters.find(name); it != _matrixParameters.end())
		{
			auto& p = it->second;
			if (p.unset || std::memcmp(&p.value[0], value.Base(), 36) != 0)
			{
				std::memcpy(&p.value[0], value.Base(), 36);
				p.unset = false;
				p.dirty = true;
			}
		}
	}

	void Material::SetParameterValue(const char* name, const Matrix4x4& value)
	{
		if (auto it = _matrixParameters.find(name); it != _matrixParameters.end())
		{
			auto& p = it->second;
			if (p.unset || std::memcmp(&p.value[0], value.Base(), 64) != 0)
			{
				std::memcpy(&p.value[0], value.Base(), 64);
				p.unset = false;
				p.dirty = true;
			}
		}
	}

	void Material::SetParameterValue(const char* name, const Texture* value)
	{
		SetParameterValue(name, value, TextureSampler::GetDefault().get());
	}

	void Material::SetParameterValue(const char* name, const Texture* value, const TextureSampler* sampler)
	{
		if (!value)
		{
			return;
		}

		if (auto it = _textureParameters.find(name); it != _textureParameters.end())
		{
			auto& p = it->second;
			auto handle = value->GetHandle();
			auto samplerHandle = sampler != nullptr ? sampler->GetHandle() : TextureSampler::GetDefault()->GetHandle();

			if (p.unset || p.value != handle || p.sampler != samplerHandle)
			{
				p.value = handle;
				p.sampler = samplerHandle;
				p.unset = false;
				p.dirty = true;
			}
		}
	}
}
