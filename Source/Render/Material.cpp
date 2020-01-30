#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureSampler.h"

namespace Freeking
{
	Material::Material(std::shared_ptr<Shader> shader, PropertyGlobals* globals) :
		_shader(shader)
	{
		InitializeParameters(globals);
	}

	void Material::InitializeParameters(PropertyGlobals* globals)
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
				p.globalId = globals != nullptr ? globals->GetFloatId(name, type) : -1;
				_floatParameters.emplace(uniform.name, p);
			}
			else if (auto type = IntParameter::Property::CastType(uniform.type);
				type != IntParameter::Property::Type::Invalid)
			{
				IntParameter p;
				p.prop.type = type;
				p.location = uniform.location;
				p.prop.unset = true;
				p.globalId = globals != nullptr ? globals->GetIntId(name, type) : -1;
				_intParameters.emplace(uniform.name, p);
			}
			else if (auto type = MatrixParameter::Property::CastType(uniform.type);
				type != MatrixParameter::Property::Type::Invalid)
			{
				MatrixParameter p;
				p.prop.type = type;
				p.location = uniform.location;
				p.prop.unset = true;
				p.globalId = globals != nullptr ? globals->GetMatrixId(name, type) : -1;
				_matrixParameters.emplace(uniform.name, p);
			}
			else if (auto type = TextureParameter::Property::CastType(uniform.type);
				type != TextureParameter::Property::Type::Invalid)
			{
				TextureParameter p;
				p.prop.type = type;
				p.location = uniform.location;
				p.prop.unset = true;
				p.globalId = globals != nullptr ? globals->GetTextureId(name, type) : -1;
				p.unit = _textureParameters.size();
				_textureParameters.emplace(uniform.name, p);
			}
		}
	}

	void Material::Apply(PropertyGlobals* globals)
	{
		if (!_shader)
		{
			return;
		}

		glUseProgram(_shader->_program);

		ApplyFloatParameters(globals);
		ApplyIntParameters(globals);
		ApplyMatrixParameters(globals);
		ApplyTextureParameters(globals);
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

	void Material::ApplyFloatParameters(PropertyGlobals* globals)
	{
		using Property = FloatParameter::Property;
		using PropertyType = Property::Type;

		for (auto [name, p] : _floatParameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (globals == nullptr)
				{
					continue;
				}

				if (prop = globals->GetFloatProperty(p.globalId);
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

	void Material::ApplyIntParameters(PropertyGlobals* globals)
	{
		using Property = IntParameter::Property;
		using PropertyType = Property::Type;

		for (auto [name, p] : _intParameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (globals == nullptr)
				{
					continue;
				}

				if (prop = globals->GetIntProperty(p.globalId);
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

	void Material::ApplyMatrixParameters(PropertyGlobals* globals)
	{
		using Property = MatrixParameter::Property;
		using PropertyType = Property::Type;

		for (auto [name, p] : _matrixParameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (globals == nullptr)
				{
					continue;
				}

				if (prop = globals->GetMatrixProperty(p.globalId);
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

	void Material::ApplyTextureParameters(PropertyGlobals* globals)
	{
		using Property = TextureParameter::Property;
		using PropertyType = Property::Type;

		for (auto [name, p] : _textureParameters)
		{
			Property* prop = nullptr;

			if (p.prop.unset)
			{
				if (globals == nullptr)
				{
					continue;
				}

				if (prop = globals->GetTextureProperty(p.globalId);
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
				glBindSampler(p.unit, prop->sampler);
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
			auto& p = it->second;
			p.prop.value[0] = value;
			p.prop.unset = false;
		}
	}

	void Material::SetParameterValue(const char* name, float value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			auto& p = it->second;
			p.prop.value[0] = value;
			p.prop.unset = false;
		}
	}

	void Material::SetParameterValue(const char* name, const Vector2f& value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			auto& p = it->second;
			std::memcpy(&p.prop.value[0], value.Base(), 8);
			p.prop.unset = false;
		}
	}

	void Material::SetParameterValue(const char* name, const Vector3f& value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			auto& p = it->second;
			std::memcpy(&p.prop.value[0], value.Base(), 12);
			p.prop.unset = false;
		}
	}

	void Material::SetParameterValue(const char* name, const Vector4f& value)
	{
		if (auto it = _floatParameters.find(name); it != _floatParameters.end())
		{
			auto& p = it->second;
			std::memcpy(&p.prop.value[0], value.Base(), 16);
			p.prop.unset = false;
		}
	}

	void Material::SetParameterValue(const char* name, const Matrix3x3& value)
	{
		if (auto it = _matrixParameters.find(name); it != _matrixParameters.end())
		{
			auto& p = it->second;
			std::memcpy(&p.prop.value[0], value.Base(), 36);
			p.prop.unset = false;
		}
	}

	void Material::SetParameterValue(const char* name, const Matrix4x4& value)
	{
		if (auto it = _matrixParameters.find(name); it != _matrixParameters.end())
		{
			auto& p = it->second;
			std::memcpy(&p.prop.value[0], value.Base(), 64);
			p.prop.unset = false;
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
			p.prop.texture = value->GetHandle();
			p.prop.sampler = sampler != nullptr ? sampler->GetHandle() : TextureSampler::GetDefault()->GetHandle();
			p.prop.unset = false;
		}
	}
}
