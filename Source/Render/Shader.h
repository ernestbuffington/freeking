#pragma once

#include "AssetLibrary.h"
#include "Vector.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include <glad/gl.h>
#include <unordered_map>
#include <memory>

namespace Freeking
{
	class Texture2D;
	class TextureBuffer;
	class TextureCube;
	class TextureSampler;
	class Shader;

	class ShaderLibrary : public AssetLibrary<Shader>
	{
	public:

		void Initialize();

		std::shared_ptr<Shader> DebugLine;
		std::shared_ptr<Shader> DynamicModel;
		std::shared_ptr<Shader> Lightmapped;
		std::shared_ptr<Shader> Sprite;
		std::shared_ptr<Shader> Text;
		std::shared_ptr<Shader> Skybox;
		std::shared_ptr<Shader> Billboard;

	protected:

		virtual void UpdateLoaders() override;
	};

	class GlobalUniformBuffer
	{
	public:

		GlobalUniformBuffer();
		~GlobalUniformBuffer();

		void Initialize();
		void Update();

		struct UniformBlock
		{
			Matrix4x4 viewMatrix;
			Matrix4x4 projectionMatrix;
			Matrix4x4 viewProjectionMatrix;
		};

		UniformBlock Uniforms;

	private:

		GLuint _bufferId;
	};

	class Shader
	{
	public:

		static ShaderLibrary Library;
		static GlobalUniformBuffer GlobalUniforms;

		static void Initialize();

		Shader() = delete;
		Shader(const std::string&);
		~Shader();

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
		void SetParameterValue(const char*, const TextureCube*, const TextureSampler*);

		void SetParameterValue(int, int);
		void SetParameterValue(int, float);
		void SetParameterValue(int, const Vector2f&);
		void SetParameterValue(int, const Vector3f&);
		void SetParameterValue(int, const Vector4f&);
		void SetParameterValue(int, const Matrix3x3&);
		void SetParameterValue(int, const Matrix4x4&);
		void SetParameterValue(int, const Texture2D*);
		void SetParameterValue(int, const Texture2D*, const TextureSampler*);
		void SetParameterValue(int, const TextureBuffer*);
		void SetParameterValue(int, const TextureCube*, const TextureSampler*);

		int GetFloatParameterId(const std::string& name) { return _floatParameters.GetId(name); }
		int GetIntParameterId(const std::string& name) { return _intParameters.GetId(name); }
		int GetMatrixParameterId(const std::string& name) { return _matrixParameters.GetId(name); }
		int GetTextureParameterId(const std::string& name) { return _textureParameters.GetId(name); }

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
				bool dirty;
			};

			Property prop;
			GLint location;
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
				bool dirty;
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
				bool dirty;
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
					Tex1D, Tex2D, Tex3D, TexBuffer, TexCube, Invalid
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
					case GL_SAMPLER_CUBE: return Type::TexCube;
					}

					return Type::Invalid;
				}

				inline static GLenum CastTargetType(Type type)
				{
					switch (type)
					{
					case Type::Tex1D: return GL_TEXTURE_1D;
					case Type::Tex2D: return GL_TEXTURE_2D;
					case Type::Tex3D: return GL_TEXTURE_3D;
					case Type::TexBuffer: return GL_TEXTURE_BUFFER;
					case Type::TexCube: return GL_TEXTURE_CUBE_MAP;
					}

					return GL_INVALID_ENUM;
				}

				void SetTexture(const Texture2D*, const TextureSampler*);
				void SetTexture(const TextureBuffer*);
				void SetTexture(const TextureCube*, const TextureSampler*);

				Type type;
				GLenum targetType;
				GLuint textureId;
				GLuint samplerId;
				bool unset;
			};

			Property prop;
			GLint location;
			int globalId;
			int unit;
		};

	private:

		using FloatPropertyType = FloatParameter::Property::Type;
		using IntPropertyType = IntParameter::Property::Type;
		using MatrixPropertyType = MatrixParameter::Property::Type;
		using TexturePropertyType = TextureParameter::Property::Type;

		void InitializeParameter(const std::string& name, GLint location, GLenum glType);
		void ApplyFloatParameters();
		void ApplyIntParameters();
		void ApplyMatrixParameters();
		void ApplyTextureParameters();

		template <typename T>
		struct Parameters
		{
			T& AddParameter(const std::string& name)
			{
				if (auto it = _parameterNameIds.find(name);
					it != _parameterNameIds.end())
				{
					return _parameters.at(it->second);
				}

				int id = static_cast<int>(_parameters.size());
				auto& param = _parameters.emplace_back();
				_parameterNameIds.emplace(name, id);

				return param;
			}

			int GetId(const std::string& name)
			{
				if (auto it = _parameterNameIds.find(name);
					it != _parameterNameIds.end())
				{
					return it->second;
				}

				return -1;
			}

			T* GetParameter(const std::string& name)
			{
				return GetParameter(GetId(name));
			}

			T* GetParameter(int id)
			{
				if (id < 0 || id > _parameters.size())
				{
					return nullptr;
				}

				return &_parameters.at(id);
			}

			size_t GetCount() const { return _parameters.size(); }

			std::vector<T> _parameters;
			std::unordered_map<std::string, int> _parameterNameIds;
		};

		GLuint _program;
		Parameters<FloatParameter> _floatParameters;
		Parameters<IntParameter> _intParameters;
		Parameters<MatrixParameter> _matrixParameters;
		Parameters<TextureParameter> _textureParameters;

		struct TextureBindingState
		{
			TextureBindingState() :
				textureId(0),
				samplerId(0)
			{
			}

			GLuint textureId;
			GLuint samplerId;
		};

		static std::vector<TextureBindingState> _textureBindingStates;
		static GLuint _activeProgramId;
	};
}
