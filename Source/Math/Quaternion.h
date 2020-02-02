#pragma once

#include "Vector.h"
#include <sstream>

namespace Freeking
{
	class Matrix3x3;
	class Matrix4x4;

	class Quaternion
	{

	public:

		Quaternion();
		Quaternion(float x, float y, float z, float w);

		void Normalise();
		float Length() const;
		float Dot(const Quaternion& q) const;
		float Angle() const;
		Quaternion Conjugate() const;
		Quaternion Inverse() const;
		Matrix3x3 ToMatrix3x3() const;
		Matrix4x4 ToMatrix4x4() const;
		Vector3f ToRadianAngles() const;
		Vector3f ToDegreeAngles() const;
		std::string ToString() const;
		Quaternion Add(const Quaternion& q) const;
		Quaternion Sub(const Quaternion& q) const;
		Quaternion Mul(const Quaternion& q) const;
		Quaternion Div(const Quaternion& q) const;
		const Quaternion& AddEq(const Quaternion& q);
		const Quaternion& SubEq(const Quaternion& q);
		const Quaternion& MulEq(const Quaternion& q);
		static Quaternion Interpolate(const Quaternion& a, const Quaternion& b, float t);
		static void Slerp(const Quaternion& from, const Quaternion& to, float fraction, Quaternion& result);
		static Quaternion FromAxisAngle(const Vector3f& axis, float angle);
		static Quaternion FromRadianAngles(const Vector3f& angle);
		static Quaternion FromRadianAngles(float pitch, float yaw, float roll);
		static Quaternion FromDegreeAngles(const Vector3f& angle);
		static Quaternion FromDegreeAngles(float pitch, float yaw, float roll);
		static Quaternion FromDegreePitch(float pitch);
		static Quaternion FromDegreeYaw(float yaw);
		static Quaternion FromDegreeRoll(float roll);
		static Quaternion FromRadianYaw(float yaw);

		Vector3f operator*(const Vector3f& v) const;
		Quaternion operator+(const Quaternion& v) const;
		Quaternion operator-(const Quaternion& v) const;
		Quaternion operator*(const Quaternion& v) const;
		Quaternion operator*(float v) const;
		Quaternion operator/(float v) const;
		Quaternion operator-() const;
		const Quaternion& operator+=(const Quaternion& v);
		const Quaternion& operator-=(const Quaternion& v);
		const Quaternion& operator*=(const Quaternion& v);
		const Quaternion& operator*=(float v);
		inline float& operator[](int index) { return *(((float*)this) + index); }
		inline const float& operator[](int index) const { return *(((const float*)this) + index); }

		float x, y, z, w;
	};
}
