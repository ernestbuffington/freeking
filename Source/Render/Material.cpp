#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Texture2D.h"
#include "TextureBuffer.h"
#include "TextureSampler.h"

namespace Freeking
{
	Material::Material(std::shared_ptr<Shader> shader, PropertyGlobals* globals) :
		_shader(shader),
		_globals(globals)
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
			if (auto type = FloatParameter::Property::CastType(uniform.type);
				type != FloatParameter::Property::Type::Invalid)
			{
				FloatParameter p;
				p.prop.type = type;
				p.location = uniform.location;
				p.prop.unset = true;
				p.globalId = _globals != nullptr ? _globals->GetFloatId(name, type) : -1;
				_floatParameters.emplace(uniform.name, p);
			}
			else if (auto type = IntParameter::Property::CastType(uniform.type);
				type != IntParameter::Property::Type::Invalid)
			{
				IntParameter p;
				p.prop.type = type;
				p.location = uniform.location;
				p.prop.unset = true;
				p.globalId = _globals != nullptr ? _globals->GetIntId(name, type) : -1;
				_intParameters.emplace(uniform.name, p);
			}
			else if (auto type = MatrixParameter::Property::CastType(uniform.type);
				type != MatrixParameter::Property::Type::Invalid)
			{
				MatrixParameter p;
				p.prop.type = type;
				p.location = uniform.location;
				p.prop.unset = true;
				p.globalId = _globals != nullptr ? _globals->GetMatrixId(name, type) : -1;
				_matrixParameters.emplace(uniform.name, p);
			}
			else if (auto type = TextureParameter::Property::CastType(uniform.type);
				type != TextureParameter::Property::Type::Invalid)
			{
				TextureParameter p;
				p.prop.type = type;
				p.location = uniform.location;
				p.prop.unset = true;
				p.globalId = _globals != nullptr ? _globals->GetTextureId(name, type) : -1;
				p.unit = _textureParameters.size();
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
		using Property = FloatParameter::Property;
		using PropertyType = Property::Type;

		for (auto [name, p] : _floatParameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (_globals == nullptr)
				{
					continue;
				}

				if (prop = _globals->GetFloatProperty(p.globalId);
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

	void Material::ApplyIntParameters()
	{
		using Property = IntParameter::Property;
		using PropertyType = Property::Type;

		for (auto [name, p] : _intParameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (_globals == nullptr)
				{
					continue;
				}

				if (prop = _globals->GetIntProperty(p.globalId);
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

	void Material::ApplyMatrixParameters()
	{
		using Property = MatrixParameter::Property;
		using PropertyType = Property::Type;

		for (auto [name, p] : _matrixParameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (_globals == nullptr)
				{
					continue;
				}

				if (prop = _globals->GetMatrixProperty(p.globalId);
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

	void Material::ApplyTextureParameters()
	{
		using Property = TextureParameter::Property;
		using PropertyType = Property::Type;

		for (auto [name, p] : _textureParameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (_globals == nullptr)
				{
					continue;
				}

				if (prop = _globals->GetTextureProperty(p.globalId);
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
			}

			if (textureType != GL_INVALID_ENUM)
			{
				glBindSampler(p.unit, prop->sampler != GL_INVALID_INDEX ? prop->sampler : 0);
				glActiveTexture(GL_TEXTURE0 + p.unit);
				glBindTexture(textureType, prop->texture);
				glUniform1i(p.location, p.unit);
			}
		}
	}

	void Material::SetParameterValue(const char* name, int value)
	{
		if (auto it = _intParameters.find(name); it != _intParameters.end())
		{
			it->second.prop.SetInt(value);
		}
	}

	void Material::SetParameterValue(const char* name, float value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			it->second.prop.SetFloat(value);
		}
	}

	void Material::SetParameterValue(const char* name, const Vector2f& value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			it->second.prop.SetVec2(value);
		}
	}

	void Material::SetParameterValue(const char* name, const Vector3f& value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			it->second.prop.SetVec3(value);
		}
	}

	void Material::SetParameterValue(const char* name, const Vector4f& value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			it->second.prop.SetVec4(value);
		}
	}

	void Material::SetParameterValue(const char* name, const Matrix3x3& value)
	{
		if (auto it = _matrixParameters.find(name); it != _matrixParameters.end())
		{
			it->second.prop.SetMat3(value);
		}
	}

	void Material::SetParameterValue(const char* name, const Matrix4x4& value)
	{
		if (auto it = _matrixParameters.find(name); it != _matrixParameters.end())
		{
			it->second.prop.SetMat4(value);
		}
	}

	void Material::SetParameterValue(const char* name, const Texture2D* value)
	{
		SetParameterValue(name, value, TextureSampler::GetDefault().get());
	}

	void Material::SetParameterValue(const char* name, const Texture2D* texture, const TextureSampler* sampler)
	{
		if (!texture)
		{
			return;
		}

		if (auto it = _textureParameters.find(name); it != _textureParameters.end())
		{
			it->second.prop.SetTexture(texture, sampler);
		}
	}

	void Material::SetParameterValue(const char* name, const TextureBuffer* texture)
	{
		if (!texture)
		{
			return;
		}

		if (auto it = _textureParameters.find(name); it != _textureParameters.end())
		{
			it->second.prop.SetTexture(texture);
		}
	}

	void Material::FloatParameter::Property::SetFloat(float value)
	{
		if (type == Type::Float)
		{
			this->value[0] = value;
			unset = false;
		}
	}

	void Material::FloatParameter::Property::SetVec2(const Vector2f& value)
	{
		if (type == Type::Vec2)
		{
			std::memcpy(&this->value[0], value.Base(), 8);
			unset = false;
		}
	}

	void Material::FloatParameter::Property::SetVec3(const Vector3f& value)
	{
		if (type == Type::Vec3)
		{
			std::memcpy(&this->value[0], value.Base(), 12);
			unset = false;
		}
	}

	void Material::FloatParameter::Property::SetVec4(const Vector4f& value)
	{
		if (type == Type::Vec4)
		{
			std::memcpy(&this->value[0], value.Base(), 16);
			unset = false;
		}
	}

	void Material::IntParameter::Property::SetInt(int value)
	{
		if (type == Type::Int)
		{
			this->value[0] = value;
			unset = false;
		}
	}

	void Material::MatrixParameter::Property::SetMat3(const Matrix3x3& value)
	{
		if (type == Type::Mat3)
		{
			std::memcpy(&this->value[0], value.Base(), 36);
			unset = false;
		}
	}

	void Material::MatrixParameter::Property::SetMat4(const Matrix4x4& value)
	{
		if (type == Type::Mat4)
		{
			std::memcpy(&this->value[0], value.Base(), 64);
			unset = false;
		}
	}

	void Material::TextureParameter::Property::SetTexture(const Texture2D* texture, const TextureSampler* sampler)
	{
		if (type == Type::Tex2D && texture)
		{
			this->texture = texture->GetHandle();
			this->sampler = sampler != nullptr ? sampler->GetHandle() : TextureSampler::GetDefault()->GetHandle();
			unset = false;
		}
	}

	void Material::TextureParameter::Property::SetTexture(const TextureBuffer* texture)
	{
		if (type == Type::TexBuffer && texture)
		{
			this->texture = texture->GetHandle();
			this->sampler = GL_INVALID_INDEX;
			unset = false;
		}
	}

	void Material::PropertyGlobals::SetValue(const char* name, int value)
	{
		if (auto p = GetIntProperty(GetIntId(name, IntPropertyType::Int));
			p != nullptr && p->type == IntPropertyType::Int)
		{
			p->SetInt(value);
		}
	}

	void Material::PropertyGlobals::SetValue(const char* name, float value)
	{
		if (auto p = GetFloatProperty(GetFloatId(name, FloatPropertyType::Float));
			p != nullptr && p->type == FloatPropertyType::Float)
		{
			p->SetFloat(value);
		}
	}

	void Material::PropertyGlobals::SetValue(const char* name, const Vector2f& value)
	{
		if (auto p = GetFloatProperty(GetFloatId(name, FloatPropertyType::Vec2));
			p != nullptr && p->type == FloatPropertyType::Vec2)
		{
			p->SetVec2(value);
		}
	}

	void Material::PropertyGlobals::SetValue(const char* name, const Vector3f& value)
	{
		if (auto p = GetFloatProperty(GetFloatId(name, FloatPropertyType::Vec3));
			p != nullptr && p->type == FloatPropertyType::Vec3)
		{
			p->SetVec3(value);
		}
	}

	void Material::PropertyGlobals::SetValue(const char* name, const Vector4f& value)
	{
		if (auto p = GetFloatProperty(GetFloatId(name, FloatPropertyType::Vec4));
			p != nullptr && p->type == FloatPropertyType::Vec4)
		{
			p->SetVec4(value);
		}
	}

	void Material::PropertyGlobals::SetValue(const char* name, const Matrix3x3& value)
	{
		if (auto p = GetMatrixProperty(GetMatrixId(name, MatrixPropertyType::Mat3));
			p != nullptr && p->type == MatrixPropertyType::Mat3)
		{
			p->SetMat3(value);
		}
	}

	void Material::PropertyGlobals::SetValue(const char* name, const Matrix4x4& value)
	{
		if (auto p = GetMatrixProperty(GetMatrixId(name, MatrixPropertyType::Mat4));
			p != nullptr && p->type == MatrixPropertyType::Mat4)
		{
			p->SetMat4(value);
		}
	}

	void Material::PropertyGlobals::SetValue(const char* name, const Texture2D* texture)
	{
		if (texture != nullptr)
		{
			SetValue(name, texture, TextureSampler::GetDefault().get());
		}
	}

	void Material::PropertyGlobals::SetValue(const char* name, const Texture2D* texture, const TextureSampler* sampler)
	{
		if (texture == nullptr)
		{
			return;
		}

		if (auto p = GetTextureProperty(GetTextureId(name, TexturePropertyType::Tex2D));
			p != nullptr && p->type == TexturePropertyType::Tex2D)
		{
			p->SetTexture(texture, sampler);
		}
	}

	void Material::PropertyGlobals::SetValue(const char* name, const TextureBuffer* texture)
	{
		if (texture == nullptr)
		{
			return;
		}

		if (auto p = GetTextureProperty(GetTextureId(name, TexturePropertyType::TexBuffer));
			p != nullptr && p->type == TexturePropertyType::TexBuffer)
		{
			p->SetTexture(texture);
		}
	}
}
