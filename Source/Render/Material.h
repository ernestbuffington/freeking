#pragma once

#include "Vector.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include <glad/glad.h>
#include <unordered_map>
#include <memory>

namespace Freeking
{
	class Texture;
	class Texture2D;
	class TextureBuffer;
	class TextureSampler;
	class Shader;

	class Material
	{
	public:

		class PropertyGlobals;

		Material() = delete;
		Material(std::shared_ptr<Shader>, PropertyGlobals* globals = nullptr);

		void Apply();
		void Unbind();

		void SetParameterValue(const char*, int);
		void SetParameterValue(const char*, float);
		void SetParameterValue(const char*, const Vector2f&);
		void SetParameterValue(const char*, const Vector3f&);
		void SetParameterValue(const char*, const Vector4f&);
		void SetParameterValue(const char*, const Matrix3x3&);
		void SetParameterValue(const char*, const Matrix4x4&);
		void SetParameterValue(const char*, const Texture2D*);
		void SetParameterValue(const char*, const Texture2D*, const TextureSampler*);
		void SetParameterValue(const char*, const TextureBuffer*);

		struct FloatParameter
		{
			struct Property
			{
				enum class Type : uint8_t
				{
					Float, Vec2, Vec3, Vec4, Mat3, Mat4, Invalid
				};

				inline static Type CastType(GLenum type)
				{
					switch (type)
					{
					case GL_FLOAT: return Type::Float;
					case GL_FLOAT_VEC2: return Type::Vec2;
					case GL_FLOAT_VEC3: return Type::Vec3;
					case GL_FLOAT_VEC4: return Type::Vec4;
					}

					return Type::Invalid;
				}

				void SetFloat(float);
				void SetVec2(const Vector2f&);
				void SetVec3(const Vector3f&);
				void SetVec4(const Vector4f&);

				Type type;
				float value[4];
				bool unset;
			};

			Property prop;
			GLint location;
			int globalId;
		};

		struct IntParameter
		{
			struct Property
			{
				enum class Type : uint8_t
				{
					Int, Vec2, Vec3, Vec4, Invalid
				};

				inline static Type CastType(GLenum type)
				{
					switch (type)
					{
					case GL_INT: return Type::Int;
					case GL_INT_VEC2: return Type::Vec2;
					case GL_INT_VEC3: return Type::Vec3;
					case GL_INT_VEC4: return Type::Vec4;
					}

					return Type::Invalid;
				}

				void SetInt(int);

				Type type;
				int value[4];
				bool unset;
			};

			Property prop;
			GLint location;
			int globalId;
		};

		struct MatrixParameter
		{
			struct Property
			{
				enum class Type : uint8_t
				{
					Mat3, Mat4, Invalid
				};

				inline static Type CastType(GLenum type)
				{
					switch (type)
					{
					case GL_FLOAT_MAT3: return Type::Mat3;
					case GL_FLOAT_MAT4: return Type::Mat4;
					}

					return Type::Invalid;
				}

				void SetMat3(const Matrix3x3&);
				void SetMat4(const Matrix4x4&);

				Type type;
				float value[16];
				bool unset;
			};

			Property prop;
			GLint location;
			int globalId;
		};

		struct TextureParameter
		{
			struct Property
			{
				enum class Type : uint8_t
				{
					Tex1D, Tex2D, Tex3D, TexBuffer, Invalid
				};

				inline static Type CastType(GLenum type)
				{
					switch (type)
					{
					case GL_SAMPLER_1D: return Type::Tex1D;
					case GL_SAMPLER_2D: return Type::Tex2D;
					case GL_SAMPLER_3D: return Type::Tex3D;
					case GL_SAMPLER_BUFFER: return Type::TexBuffer;
					case GL_INT_SAMPLER_BUFFER: return Type::TexBuffer;
					case GL_UNSIGNED_INT_SAMPLER_BUFFER: return Type::TexBuffer;
					}

					return Type::Invalid;
				}

				void SetTexture(const Texture2D*, const TextureSampler*);
				void SetTexture(const TextureBuffer*);

				Type type;
				GLuint texture;
				GLuint sampler;
				bool unset;
			};

			Property prop;
			GLint location;
			int globalId;
			int unit;
		};

		class PropertyGlobals
		{
		public:

			using FloatPropertyType = FloatParameter::Property::Type;
			using IntPropertyType = IntParameter::Property::Type;
			using MatrixPropertyType = MatrixParameter::Property::Type;
			using TexturePropertyType = TextureParameter::Property::Type;

			void SetValue(const char*, int);
			void SetValue(const char*, float);
			void SetValue(const char*, const Vector2f&);
			void SetValue(const char*, const Vector3f&);
			void SetValue(const char*, const Vector4f&);
			void SetValue(const char*, const Matrix3x3&);
			void SetValue(const char*, const Matrix4x4&);
			void SetValue(const char*, const Texture2D*);
			void SetValue(const char*, const Texture2D*, const TextureSampler*);
			void SetValue(const char*, const TextureBuffer*);

			int GetFloatId(const std::string& name, FloatPropertyType type) { return _floatProperties.GetId(name, type); }
			int GetIntId(const std::string& name, IntPropertyType type) { return _intProperties.GetId(name, type); }
			int GetMatrixId(const std::string& name, MatrixPropertyType type) { return _matrixProperties.GetId(name, type); }
			int GetTextureId(const std::string& name, TexturePropertyType type) { return _textureProperties.GetId(name, type); }

			FloatParameter::Property* GetFloatProperty(int id) { return _floatProperties.GetProperty(id); }
			IntParameter::Property* GetIntProperty(int id) { return _intProperties.GetProperty(id); }
			MatrixParameter::Property* GetMatrixProperty(int id) { return _matrixProperties.GetProperty(id); }
			TextureParameter::Property* GetTextureProperty(int id) { return _textureProperties.GetProperty(id); }

		private:

			template <typename T>
			struct Properties
			{
				int GetId(const std::string& name, const enum class T::Type& type)
				{
					if (auto it = _propertyNameIds.find(name);
						it != _propertyNameIds.end())
					{
						return it->second;
					}

					int id = _properties.size();

					T prop;
					prop.type = type;
					prop.unset = true;
					_properties.push_back(prop);
					_propertyNameIds.emplace(name, id);

					return id;
				}

				T* GetProperty(int id)
				{
					if (id < 0 || id > _properties.size())
					{
						return nullptr;
					}

					return &_properties.at(id);
				}

				std::vector<T> _properties;
				std::unordered_map<std::string, int> _propertyNameIds;
			};

			Properties<FloatParameter::Property> _floatProperties;
			Properties<IntParameter::Property> _intProperties;
			Properties<MatrixParameter::Property> _matrixProperties;
			Properties<TextureParameter::Property> _textureProperties;
		};

	private:

		void InitializeParameters();
		void ApplyFloatParameters();
		void ApplyIntParameters();
		void ApplyMatrixParameters();
		void ApplyTextureParameters();

		std::shared_ptr<Shader> _shader;
		std::unordered_map<std::string, FloatParameter> _floatParameters;
		std::unordered_map<std::string, IntParameter> _intParameters;
		std::unordered_map<std::string, MatrixParameter> _matrixParameters;
		std::unordered_map<std::string, TextureParameter> _textureParameters;
		PropertyGlobals* _globals;
	};
}
