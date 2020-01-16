#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Math.h"

namespace Freeking
{
	Matrix3x3::Matrix3x3()
	{
		Identity();
	}

	Matrix3x3::Matrix3x3(const Vector3f& c0, const Vector3f& c1, const Vector3f& c2)
	{
		m[0] = c0;
		m[1] = c1;
		m[2] = c2;
	}

	void Matrix3x3::Identity()
	{
		m[0] = Vector3f(1, 0, 0);
		m[1] = Vector3f(0, 1, 0);
		m[2] = Vector3f(0, 0, 1);
	}

	Matrix3x3 Matrix3x3::Transpose() const
	{
		Vector3f r0 = m[0];
		Vector3f r1 = m[1];
		Vector3f r2 = m[2];

		return Matrix3x3(Vector3f(r0.x, r1.x, r2.x),
			Vector3f(r0.y, r1.y, r2.y),
			Vector3f(r0.z, r1.z, r2.z));
	}

	void Matrix3x3::RotationX(Matrix3x3& matrix, float angle)
	{
		matrix.m[0][0] = 1; matrix.m[0][1] = 0; matrix.m[0][2] = 0;
		matrix.m[1][0] = 0; matrix.m[1][1] = cos(angle); matrix.m[1][2] = -sin(angle);
		matrix.m[2][0] = 0; matrix.m[2][1] = sin(angle); matrix.m[2][2] = cos(angle);
	}

	void Matrix3x3::RotationY(Matrix3x3& matrix, float angle)
	{
		matrix.m[0][0] = cos(angle); matrix.m[0][1] = 0; matrix.m[0][2] = sin(angle);
		matrix.m[1][0] = 0; matrix.m[1][1] = 1;	matrix.m[1][2] = 0;
		matrix.m[2][0] = -sin(angle); matrix.m[2][1] = 0; matrix.m[2][2] = cos(angle);
	}

	void Matrix3x3::RotationZ(Matrix3x3& matrix, float angle)
	{
		matrix.m[0][0] = cos(angle); matrix.m[0][1] = -sin(angle); matrix.m[0][2] = 0;
		matrix.m[1][0] = sin(angle); matrix.m[1][1] = cos(angle); matrix.m[1][2] = 0;
		matrix.m[2][0] = 0; matrix.m[2][1] = 0; matrix.m[2][2] = 1;
	}

	void Matrix3x3::RotationXYZ(Matrix3x3& matrix, const Vector3f& angles)
	{
		Matrix3x3 x, y, z;
		Matrix3x3::RotationX(x, angles.x);
		Matrix3x3::RotationY(y, angles.y);
		Matrix3x3::RotationZ(z, angles.z);
		matrix = (z * y * x);
	}

	void Matrix3x3::Scale(Matrix3x3& matrix, const Vector3f& scale)
	{
		matrix.m[0][0] = scale.x; matrix.m[0][1] = 0; matrix.m[0][2] = 0;
		matrix.m[1][0] = 0; matrix.m[1][1] = scale.y; matrix.m[1][2] = 0;
		matrix.m[2][0] = 0; matrix.m[2][1] = 0; matrix.m[2][2] = scale.z;
	}

	void Matrix3x3::Scale(Matrix3x3& matrix, float scale)
	{
		Scale(matrix, Vector3f(scale, scale, scale));
	}

	Matrix3x3 Matrix3x3::Scale(const Vector3f& scale)
	{
		Matrix3x3 matrix;
		Scale(matrix, scale);

		return matrix;
	}

	Matrix3x3 Matrix3x3::Scale(float scale)
	{
		Matrix3x3 matrix;
		Scale(matrix, scale);

		return matrix;
	}

	Matrix3x3 Matrix3x3::RotationX(float angle)
	{
		Matrix3x3 x;
		RotationX(x, angle);

		return x;
	}

	Matrix3x3 Matrix3x3::RotationY(float angle)
	{
		Matrix3x3 y;
		RotationY(y, angle);

		return y;
	}

	Matrix3x3 Matrix3x3::RotationZ(float angle)
	{
		Matrix3x3 z;
		RotationZ(z, angle);

		return z;
	}

	Matrix3x3 Matrix3x3::RotationXYZ(const Vector3f& angles)
	{
		Matrix3x3 xyz;
		RotationXYZ(xyz, angles);

		return xyz;
	}

	void Matrix3x3::RotationAxis(Matrix3x3& matrix, const Vector3f& axis, float angle)
	{
		float sinTheta = sin(angle);
		float cosTheta = cos(angle);
		float oneMinusCosTheta = 1 - cosTheta;
		float axisXSquared = axis.x * axis.x;
		float axisYSquared = axis.y * axis.y;
		float axisZSquared = axis.z * axis.z;

		matrix.m[0][0] = axisXSquared + (1 - axisXSquared) * cosTheta;
		matrix.m[0][1] = axis.x * axis.y * oneMinusCosTheta - axis.z * sinTheta;
		matrix.m[0][2] = axis.x * axis.z * oneMinusCosTheta + axis.y * sinTheta;

		matrix.m[1][0] = axis.x * axis.y * oneMinusCosTheta + axis.z * sinTheta;
		matrix.m[1][1] = axisYSquared + (1 - axisYSquared) * cosTheta;
		matrix.m[1][2] = axis.y * axis.z * oneMinusCosTheta - axis.x * sinTheta;

		matrix.m[2][0] = axis.x * axis.y * oneMinusCosTheta - axis.y * sinTheta;
		matrix.m[2][1] = axis.y * axis.z * oneMinusCosTheta + axis.x * sinTheta;
		matrix.m[2][2] = axisZSquared + (1 - axisZSquared) * cosTheta;
	}

	Matrix3x3 Matrix3x3::LookAt(const Vector3f& forward, Vector3f up)
	{
		Vector3f right = forward.Cross(up).Normalise();
		up = right.Cross(forward).Normalise();

		return Matrix3x3(Vector3f(right.x, right.y, right.z),
			Vector3f(up.x, up.y, up.z),
			Vector3f(-forward.x, -forward.y, -forward.z));
	}

	Vector3f Matrix3x3::ToRadianAngles() const
	{
		Vector3f angles;
		float s = sqrt(m[0][0] * m[0][0] + m[0][1] * m[0][1]);

		if (s > Math::EPSILON)
		{
			angles.x = -atan2(m[0][2], s);
			angles.y = atan2(m[0][1], m[0][0]);
			angles.z = atan2(m[1][2], m[2][2]);
		}
		else
		{
			angles.x = m[0][2] < 0.0f ? 90.0f : -90.0f;
			angles.y = -atan2(m[1][0], m[1][1]);
			angles.z = 0.0f;
		}

		return angles;
	}

	Vector3f Matrix3x3::ToDegreeAngles() const
	{
		Vector3f angles = ToRadianAngles();
		angles.x = Math::RadiansToDegrees(angles.x);
		angles.y = Math::RadiansToDegrees(angles.y);
		angles.z = Math::RadiansToDegrees(angles.z);

		return angles;
	}

	Vector3f Matrix3x3::Transform(const Vector3f& v) const
	{
		return Vector3f(Row(0).Dot(v),
			Row(1).Dot(v),
			Row(2).Dot(v));
	}

	Matrix3x3 Matrix3x3::operator+(const Matrix3x3& matrix) const
	{
		Matrix3x3 r;

		r.m[0][0] = m[0][0] + matrix.m[0][0];
		r.m[0][1] = m[0][1] + matrix.m[0][1];
		r.m[0][2] = m[0][2] + matrix.m[0][2];

		r.m[1][0] = m[1][0] + matrix.m[1][0];
		r.m[1][1] = m[1][1] + matrix.m[1][1];
		r.m[1][2] = m[1][2] + matrix.m[1][2];

		r.m[2][0] = m[2][0] + matrix.m[2][0];
		r.m[2][1] = m[2][1] + matrix.m[2][1];
		r.m[2][2] = m[2][2] + matrix.m[2][2];

		return r;
	}

	Matrix3x3 Matrix3x3::operator*(const Matrix3x3& matrix) const
	{
		Matrix3x3 r;

		r.m[0][0] = m[0][0] * matrix.m[0][0] + m[0][1] * matrix.m[1][0] + m[0][2] * matrix.m[2][0];
		r.m[0][1] = m[0][0] * matrix.m[0][1] + m[0][1] * matrix.m[1][1] + m[0][2] * matrix.m[2][1];
		r.m[0][2] = m[0][0] * matrix.m[0][2] + m[0][1] * matrix.m[1][2] + m[0][2] * matrix.m[2][2];

		r.m[1][0] = m[1][0] * matrix.m[0][0] + m[1][1] * matrix.m[1][0] + m[1][2] * matrix.m[2][0];
		r.m[1][1] = m[1][0] * matrix.m[0][1] + m[1][1] * matrix.m[1][1] + m[1][2] * matrix.m[2][1];
		r.m[1][2] = m[1][0] * matrix.m[0][2] + m[1][1] * matrix.m[1][2] + m[1][2] * matrix.m[2][2];

		r.m[2][0] = m[2][0] * matrix.m[0][0] + m[2][1] * matrix.m[1][0] + m[2][2] * matrix.m[2][0];
		r.m[2][1] = m[2][0] * matrix.m[0][1] + m[2][1] * matrix.m[1][1] + m[2][2] * matrix.m[2][1];
		r.m[2][2] = m[2][0] * matrix.m[0][2] + m[2][1] * matrix.m[1][2] + m[2][2] * matrix.m[2][2];

		return r;
	}

	const Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& matrix)
	{
		return *this = *this * matrix;
	}

	Vector3f operator*(const Vector3f& lhs, const Matrix3x3& rhs)
	{
		Vector3f v(rhs.m[0][0] * lhs.x + rhs.m[1][0] * lhs.y + rhs.m[2][0] * lhs.z,
			rhs.m[0][1] * lhs.x + rhs.m[1][1] * lhs.y + rhs.m[2][1] * lhs.z,
			rhs.m[0][2] * lhs.x + rhs.m[1][2] * lhs.y + rhs.m[2][2] * lhs.z);

		return v;
	}

	Matrix4x4 Matrix3x3::ToMatrix4x4()
	{
		Matrix4x4 r;

		r[0][0] = m[0][0]; r[1][0] = m[0][1]; r[2][0] = m[0][2]; r[3][0] = 0;
		r[0][1] = m[1][0]; r[1][1] = m[1][1]; r[2][1] = m[1][2]; r[3][1] = 0;
		r[0][2] = m[2][0]; r[1][2] = m[2][1]; r[2][2] = m[2][2]; r[3][2] = 0;
		r[0][3] = 0; r[1][3] = 0; r[2][3] = 0; r[3][3] = 1;

		return r;
	}

	const float* Matrix3x3::Base() const
	{
		return m[0].Base();
	}

	float* Matrix3x3::Base()
	{
		return m[0].Base();
	}
}
