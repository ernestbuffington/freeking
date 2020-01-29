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
	class TextureSampler;
	class ShaderProgram;

	class Material
	{
	public:

		Material() = delete;
		Material(std::shared_ptr<ShaderProgram>);

		void Apply();
		void Unbind();

		void SetParameterValue(const char*, int);
		void SetParameterValue(const char*, float);
		void SetParameterValue(const char*, const Vector2f&);
		void SetParameterValue(const char*, const Vector3f&);
		void SetParameterValue(const char*, const Vector4f&);
		void SetParameterValue(const char*, const Matrix3x3&);
		void SetParameterValue(const char*, const Matrix4x4&);
		void SetParameterValue(const char*, const Texture*);
		void SetParameterValue(const char*, const Texture*, const TextureSampler*);

	private:

		void InitializeParameters();
		void ApplyFloatParameters();
		void ApplyIntParameters();
		void ApplyMatrixParameters();
		void ApplyTextureParameters();

		enum class FloatUniformType : uint8_t
		{
			Float, Vec2, Vec3, Vec4, Mat3, Mat4, Invalid
		};

		enum class IntUniformType : uint8_t
		{
			Int, Vec2, Vec3, Vec4, Invalid
		};

		enum class MatrixUniformType : uint8_t
		{
			Mat3, Mat4, Invalid
		};

		enum class TextureUniformType : uint8_t
		{
			Tex1D, Tex2D, Tex3D, TexBuffer, Invalid
		};

		struct FloatParameter
		{
			GLint location;
			float value[4];
			FloatUniformType type;
			bool dirty;
			bool unset;
		};

		struct IntParameter
		{
			GLint location;
			int value[4];
			IntUniformType type;
			bool dirty;
			bool unset;
		};

		struct MatrixParameter
		{
			GLint location;
			float value[16];
			MatrixUniformType type;
			bool dirty;
			bool unset;
		};

		struct TextureParameter
		{
			GLint location;
			GLuint value;
			GLuint sampler;
			TextureUniformType type;
			bool dirty;
			bool unset;
		};

		static Material::FloatUniformType ToFloatUniformType(GLenum);
		static Material::IntUniformType ToIntUniformType(GLenum);
		static Material::MatrixUniformType ToMatrixUniformType(GLenum);
		static Material::TextureUniformType ToTextureUniformType(GLenum);

		std::shared_ptr<ShaderProgram> _shader;
		std::unordered_map<std::string, FloatParameter> _floatParameters;
		std::unordered_map<std::string, IntParameter> _intParameters;
		std::unordered_map<std::string, MatrixParameter> _matrixParameters;
		std::unordered_map<std::string, TextureParameter> _textureParameters;
	};
}
