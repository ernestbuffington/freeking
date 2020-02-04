#pragma once

#include "Vector.h"
#include "Matrix4x4.h"

namespace Freeking
{
	class Matrix3x3
	{
		friend class Quaternion;

	public:

		Matrix3x3();
		Matrix3x3(const Vector3f& c0, const Vector3f& c1, const Vector3f& c2);

		void Identity();
		Matrix3x3 Transpose() const;
		static void RotationX(Matrix3x3& matrix, float angle);
		static void RotationY(Matrix3x3& matrix, float angle);
		static void RotationZ(Matrix3x3& matrix, float angle);
		static void RotationXYZ(Matrix3x3& matrix, const Vector3f& angles);
		static Matrix3x3 RotationX(float angle);
		static Matrix3x3 RotationY(float angle);
		static Matrix3x3 RotationZ(float angle);
		static Matrix3x3 RotationXYZ(const Vector3f& angles);
		static void Scale(Matrix3x3& matrix, const Vector3f& scale);
		static void Scale(Matrix3x3& matrix, float scale);
		static Matrix3x3 Scale(const Vector3f& scale);
		static Matrix3x3 Scale(float scale);
		static void RotationAxis(Matrix3x3& matrix, const Vector3f& axis, float angle);
		static Matrix3x3 LookAt(const Vector3f& forward, Vector3f up = Vector3f(0.0f, 1.0f, 0.0f));
		Vector3f ToRadianAngles() const;
		Vector3f ToDegreeAngles() const;
		Vector3f Transform(const Vector3f& v) const;
		inline Vector3f Row(int index) const { return Vector3f(m[0][index], m[1][index], m[2][index]); }
		Matrix4x4 ToMatrix4x4() const;

		Matrix3x3 operator+(const Matrix3x3& matrix) const;
		Matrix3x3 operator*(const Matrix3x3& matrix) const;
		const Matrix3x3& operator*=(const Matrix3x3& matrix);
		friend Vector3f operator*(const Vector3f& lhs, const Matrix3x3& rhs);
		inline Vector3f& operator[](unsigned int value) { return m[value]; }
		inline const Vector3f& operator[](unsigned int value) const { return m[value]; }

		const float* Base() const;

	private:

		Vector3f m[3];
	};
}
