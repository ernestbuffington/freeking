#pragma once

#include "Vector.h"
#include <ostream>

namespace Freeking
{
	class Matrix4x4
	{
	public:

		Matrix4x4();
		Matrix4x4(float xx, float xy, float xz, float xw,
			float yx, float yy, float yz, float yw,
			float zx, float zy, float zz, float zw,
			float wx, float wy, float wz, float ww);
		Matrix4x4(const Vector4f& c0, const Vector4f& c1, const Vector4f& c2, const Vector4f& c3);
		Matrix4x4(const float* matrix);

		void Identity();
		void Translate(const Vector3f& position);
		inline Vector4f Row(size_t index) const { return Vector4f(m[0][index], m[1][index], m[2][index], m[3][index]); }
		static Matrix4x4 Translation(const Vector3f& position);
		static Matrix4x4 Perspective(float fov, float aspect, float nearClip, float farClip);
		static Matrix4x4 Ortho(float left, float right, float top, float bottom, float nearClip, float farClip);
		static Matrix4x4 LookAt(const Vector3f& position, const Vector3f& direction, const Vector3f& up);
		static bool Invert(const Matrix4x4& in, Matrix4x4& out);
		Matrix4x4 Inverse() const;
		Matrix4x4 Transpose() const;
		static Matrix4x4 Scale(const Vector3f& scale);
		static Matrix4x4 Scale(float scale);
		Vector4f Transform(const Vector4f& v) const;
		Vector3f Transform(const Vector3f& v) const;
		Vector3f TransformPoint(const Vector3f& v) const;
		Vector3f TransformDirection(const Vector3f& v) const;
		void ClipProjection(const Vector4f& clipPlane);

		Matrix4x4 operator*(const Matrix4x4& rhs) const;
		void operator*=(const Matrix4x4& rhs);
		Vector4f operator*(const Vector4f& rhs) const;
		Vector3f operator*(const Vector3f& rhs) const;
		Matrix4x4 operator*(float rhs) const;
		inline Vector4f& operator[](unsigned int value) { return m[value]; }
		inline const Vector4f& operator[](unsigned int value) const { return m[value]; }

		const float* Base() const;
		float* Base();

	private:

		Vector4f m[4];
	};

	inline std::ostream& operator<<(std::ostream& out, const Matrix4x4& mat)
	{
		return out << "mat4x4(" << mat[0] << ", " << mat[1] << ", " << mat[2] << ", " << mat[3] << ")";
	}
}
