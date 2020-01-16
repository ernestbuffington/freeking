#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Math.h"
#include <cmath>

namespace Freeking
{
	Quaternion::Quaternion() :
		x(0),
		y(0),
		z(0),
		w(1)
	{

	}

	Quaternion::Quaternion(float x, float y, float z, float w) :
		x(x),
		y(y),
		z(z),
		w(w)
	{

	}

	void Quaternion::Normalise()
	{
		float length = Length();

		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	float Quaternion::Length() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	float Quaternion::Dot(const Quaternion& q) const
	{
		return x * q.x + y * q.y + z * q.z + w * q.w;
	}

	float Quaternion::Angle() const
	{
		return acosf(w) * 2.0f;
	}

	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion Quaternion::Inverse() const
	{
		const float l = 1.0f / (x * x + y * y + z * z + w * w);

		return Quaternion(-x * l, -y * l, -z * l, w * l);
	}

	Matrix3x3 Quaternion::ToMatrix3x3() const
	{
		float xx = x * x;
		float xy = x * y;
		float xz = x * z;
		float xw = x * w;

		float yy = y * y;
		float yz = y * z;
		float yw = y * w;

		float zz = z * z;
		float zw = z * w;

		Matrix3x3 r;

		r.m[0][0] = 1 - 2 * (yy + zz);
		r.m[1][0] = 2 * (xy + zw);
		r.m[2][0] = 2 * (xz - yw);

		r.m[0][1] = 2 * (xy - zw);
		r.m[1][1] = 1 - 2 * (xx + zz);
		r.m[2][1] = 2 * (yz + xw);

		r.m[0][2] = 2 * (xz + yw);
		r.m[1][2] = 2 * (yz - xw);
		r.m[2][2] = 1 - 2 * (xx + yy);

		return r;
	}

	Matrix4x4 Quaternion::ToMatrix4x4() const
	{
		return ToMatrix3x3().ToMatrix4x4();
	}

	Quaternion Quaternion::operator+(const Quaternion& v) const
	{
		return Quaternion(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	Quaternion Quaternion::operator-(const Quaternion& v) const
	{
		return Quaternion(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	Vector3f Quaternion::operator*(const Vector3f& v) const
	{
		Vector3f uv, uuv;
		Vector3f QuatVector(x, y, z);
		uv = QuatVector.Cross(v);
		uuv = QuatVector.Cross(uv);
		uv *= (2 * w);
		uuv *= 2;

		return v + uv + uuv;
	}

	Quaternion Quaternion::operator*(const Quaternion& v) const
	{
		return Quaternion(w * v.x + x * v.w + y * v.z - z * v.y,
			w * v.y + y * v.w + z * v.x - x * v.z,
			w * v.z + z * v.w + x * v.y - y * v.x,
			w * v.w - x * v.x - y * v.y - z * v.z);
	}

	Quaternion Quaternion::operator*(float v) const
	{
		return Quaternion(x * v, y * v, z * v, w * v);
	}

	Quaternion Quaternion::operator/(float v) const
	{
		return *this * (1.0f / v);
	}

	Quaternion Quaternion::operator-() const
	{
		return Quaternion(-x, -y, -z, -w);
	}

	const Quaternion& Quaternion::operator+=(const Quaternion& v)
	{
		return *this = *this + v;
	}

	const Quaternion& Quaternion::operator-=(const Quaternion& v)
	{
		return *this = *this - v;
	}

	const Quaternion& Quaternion::operator*=(const Quaternion& v)
	{
		return *this = *this * v;
	}

	const Quaternion& Quaternion::operator*=(float v)
	{
		x *= v;
		y *= v;
		z *= v;
		w *= v;

		return *this;
	}

	Quaternion Quaternion::Interpolate(const Quaternion& a, const Quaternion& b, float t)
	{
		Quaternion q = a * (1 - t) + b * t;
		q.Normalise();

		return q;
	}

	void Quaternion::Slerp(const Quaternion& from, const Quaternion& to, float fraction, Quaternion& result)
	{
		float angle = from.Dot(to);
		float sign = 1.0f;

		if (angle < 0.0f)
		{
			angle = -angle;
			sign = -1.0f;
		}

		float a;
		float b;

		if (angle <= 0.97f)
		{
			angle = acos(angle);
			float c = 1.0f / sin(angle);
			a = sin((1.0f - fraction) * angle) * c;
			b = sin(angle * fraction) * c;
		}
		else
		{
			a = 1.0f - fraction;
			b = fraction;
		}

		result = (from * (a * sign) + to * b);
		result.Normalise();
	}

	Quaternion Quaternion::FromAxisAngle(const Vector3f& axis, float angle)
	{
		float d = axis.Length();
		float s = sin(angle * 0.5f) / d;

		return Quaternion(axis.x * s, axis.y * s, axis.z * s, cos(angle * 0.5f));
	}

	Quaternion Quaternion::FromRadianAngles(const Vector3f& angles)
	{
		Quaternion q(FromAxisAngle(Vector3f(0.0f, 0.0f, 1.0f), angles.z) *
			FromAxisAngle(Vector3f(0.0f, 1.0f, 0.0f), angles.y) *
			FromAxisAngle(Vector3f(1.0f, 0.0f, 0.0f), angles.x));

		q.Normalise();

		return q;
	}

	Quaternion Quaternion::FromDegreeAngles(const Vector3f& angles)
	{
		return FromRadianAngles(Vector3f(Math::DegreesToRadians(angles.x),
			Math::DegreesToRadians(angles.y),
			Math::DegreesToRadians(angles.z)));
	}

	Vector3f Quaternion::ToRadianAngles() const
	{
		return ToMatrix3x3().ToRadianAngles();
	}

	Vector3f Quaternion::ToDegreeAngles() const
	{
		return ToRadianAngles().ToDegrees();
	}

	Quaternion Quaternion::Add(const Quaternion& q) const
	{
		return *this + q;
	}

	Quaternion Quaternion::Sub(const Quaternion& q) const
	{
		return *this - q;
	}

	Quaternion Quaternion::Mul(const Quaternion& q) const
	{
		return *this * q;
	}

	const Quaternion& Quaternion::AddEq(const Quaternion& q)
	{
		return (*this += q);
	}

	const Quaternion& Quaternion::SubEq(const Quaternion& q)
	{
		return (*this -= q);
	}

	const Quaternion& Quaternion::MulEq(const Quaternion& q)
	{
		return (*this *= q);
	}

	std::string Quaternion::ToString() const
	{
		std::stringstream stream;
		stream << x << " " << y << " " << z << " " << w;

		return stream.str();
	}
}
