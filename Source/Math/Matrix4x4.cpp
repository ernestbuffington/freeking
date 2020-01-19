#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "Maths.h"

namespace Freeking
{
	Matrix4x4::Matrix4x4()
	{
		Identity();
	}

	Matrix4x4::Matrix4x4(float xx, float xy, float xz, float xw,
		float yx, float yy, float yz, float yw,
		float zx, float zy, float zz, float zw,
		float wx, float wy, float wz, float ww)
	{
		m[0][0] = xx; m[0][1] = xy; m[0][2] = xz; m[0][3] = xw;
		m[1][0] = yx; m[1][1] = yy; m[1][2] = yz; m[1][3] = yw;
		m[2][0] = zx; m[2][1] = zy; m[2][2] = zz; m[2][3] = zw;
		m[3][0] = wx; m[3][1] = wy; m[3][2] = wz; m[3][3] = ww;
	}

	Matrix4x4::Matrix4x4(const Vector4f& c0, const Vector4f& c1, const Vector4f& c2, const Vector4f& c3)
	{
		m[0] = c0;
		m[1] = c1;
		m[2] = c2;
		m[3] = c3;
	}

	Matrix4x4::Matrix4x4(const float* matrix)
	{
		m[0] = Vector4f(matrix[0], matrix[1], matrix[2], matrix[3]);
		m[1] = Vector4f(matrix[4], matrix[5], matrix[6], matrix[7]);
		m[2] = Vector4f(matrix[8], matrix[9], matrix[10], matrix[11]);
		m[3] = Vector4f(matrix[12], matrix[13], matrix[14], matrix[15]);
	}

	void Matrix4x4::Identity()
	{
		m[0] = Vector4f(1, 0, 0, 0);
		m[1] = Vector4f(0, 1, 0, 0);
		m[2] = Vector4f(0, 0, 1, 0);
		m[3] = Vector4f(0, 0, 0, 1);
	}

	Matrix4x4 Matrix4x4::Translation(const Vector3f& position)
	{
		Matrix4x4 r;
		r[3][0] = position.x;
		r[3][1] = position.y;
		r[3][2] = position.z;

		return r;
	}

	void Matrix4x4::Translate(const Vector3f& position)
	{
		m[3][0] = position.x;
		m[3][1] = position.y;
		m[3][2] = position.z;
	}

	Matrix4x4 Matrix4x4::Perspective(float fov, float aspect, float nearClip, float farClip)
	{
		float f = 1.0f / tan(Math::DegreesToRadians(fov) / 2.0f);

		return Matrix4x4(Vector4f(f / aspect, 0, 0, 0),
			Vector4f(0, f, 0, 0),
			Vector4f(0, 0, (farClip + nearClip) / (nearClip - farClip), -1),
			Vector4f(0, 0, (2.0f * farClip * nearClip) / (nearClip - farClip), 0));
	}

	Matrix4x4 Matrix4x4::Ortho(float left, float right, float bottom, float top, float nearClip, float farClip)
	{
		Vector4f translation(-(right + left) / (right - left),
			-(top + bottom) / (top - bottom),
			-(farClip + nearClip) / (farClip - nearClip),
			1);


		return Matrix4x4(Vector4f(2 / (right - left), 0, 0, 0),
			Vector4f(0, 2 / (top - bottom), 0, 0),
			Vector4f(0, 0, 2 / (farClip - nearClip), 0),
			translation);
	}

	Matrix4x4 Matrix4x4::LookAt(const Vector3f& position, const Vector3f& forward, const Vector3f& up)
	{
		Vector3f right = forward.Cross(up).Normalise();
		Vector3f upOrtho = right.Cross(forward).Normalise();

		Matrix4x4 rotation = Matrix4x4(Vector4f(right.x, right.y, right.z, 0),
			Vector4f(upOrtho.x, upOrtho.y, upOrtho.z, 0),
			Vector4f(forward.x, forward.y, forward.z, 0),
			Vector4f(0, 0, 0, 1));

		return rotation * Matrix4x4::Translation(-position);
	}

	Vector4f Matrix4x4::Transform(const Vector4f& v) const
	{
		return Vector4f(Row(0).Dot(v),
			Row(1).Dot(v),
			Row(2).Dot(v),
			Row(3).Dot(v));
	}

	Vector3f Matrix4x4::Transform(const Vector3f& v) const
	{
		return Vector3f(Row(0).xyz().Dot(v),
			Row(1).xyz().Dot(v),
			Row(2).xyz().Dot(v));
	}

	Vector3f Matrix4x4::TransformDirection(const Vector3f& v) const
	{
		return Vector3f(Row(0).xyz().Dot(v),
			Row(1).xyz().Dot(v),
			Row(2).xyz().Dot(v));
	}

	Vector3f Matrix4x4::TransformPoint(const Vector3f& v) const
	{
		Vector4f r0 = Row(0);
		Vector4f r1 = Row(1);
		Vector4f r2 = Row(2);

		Vector3f r(r0.Dot(v) + m[3][0],
			r1.Dot(v) + m[3][1],
			r2.Dot(v) + m[3][2]);

		float w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];

		if (w != 1 && w != 0)
		{
			//r.x = r.x / w; r.y = r.y / w; r.z = r.z / w;
		}

		return r;
	}

	Matrix4x4 Matrix4x4::Inverse() const
	{
		Matrix4x4 out;
		Invert(*this, out);

		return out;
	}

	bool Matrix4x4::Invert(const Matrix4x4& in, Matrix4x4& out)
	{
		Matrix4x4 m;

		m[0][0] = in[1][1] * in[2][2] * in[3][3] - in[1][1] * in[2][3] * in[3][2] - in[2][1] * in[1][2] * in[3][3]
			+ in[2][1] * in[1][3] * in[3][2] + in[3][1] * in[1][2] * in[2][3] - in[3][1] * in[1][3] * in[2][2];
		m[1][0] = -in[1][0] * in[2][2] * in[3][3] + in[1][0] * in[2][3] * in[3][2] + in[2][0] * in[1][2] * in[3][3]
			- in[2][0] * in[1][3] * in[3][2] - in[3][0] * in[1][2] * in[2][3] + in[3][0] * in[1][3] * in[2][2];
		m[2][0] = in[1][0] * in[2][1] * in[3][3] - in[1][0] * in[2][3] * in[3][1] - in[2][0] * in[1][1] * in[3][3]
			+ in[2][0] * in[1][3] * in[3][1] + in[3][0] * in[1][1] * in[2][3] - in[3][0] * in[1][3] * in[2][1];
		m[3][0] = -in[1][0] * in[2][1] * in[3][2] + in[1][0] * in[2][2] * in[3][1] + in[2][0] * in[1][1] * in[3][2]
			- in[2][0] * in[1][2] * in[3][1] - in[3][0] * in[1][1] * in[2][2] + in[3][0] * in[1][2] * in[2][1];

		m[0][1] = -in[0][1] * in[2][2] * in[3][3] + in[0][1] * in[2][3] * in[3][2] + in[2][1] * in[0][2] * in[3][3]
			- in[2][1] * in[0][3] * in[3][2] - in[3][1] * in[0][2] * in[2][3] + in[3][1] * in[0][3] * in[2][2];
		m[1][1] = in[0][0] * in[2][2] * in[3][3] - in[0][0] * in[2][3] * in[3][2] - in[2][0] * in[0][2] * in[3][3]
			+ in[2][0] * in[0][3] * in[3][2] + in[3][0] * in[0][2] * in[2][3] - in[3][0] * in[0][3] * in[2][2];
		m[2][1] = -in[0][0] * in[2][1] * in[3][3] + in[0][0] * in[2][3] * in[3][1] + in[2][0] * in[0][1] * in[3][3]
			- in[2][0] * in[0][3] * in[3][1] - in[3][0] * in[0][1] * in[2][3] + in[3][0] * in[0][3] * in[2][1];
		m[3][1] = in[0][0] * in[2][1] * in[3][2] - in[0][0] * in[2][2] * in[3][1] - in[2][0] * in[0][1] * in[3][2]
			+ in[2][0] * in[0][2] * in[3][1] + in[3][0] * in[0][1] * in[2][2] - in[3][0] * in[0][2] * in[2][1];

		m[0][2] = in[0][1] * in[1][2] * in[3][3] - in[0][1] * in[1][3] * in[3][2] - in[1][1] * in[0][2] * in[3][3]
			+ in[1][1] * in[0][3] * in[3][2] + in[3][1] * in[0][2] * in[1][3] - in[3][1] * in[0][3] * in[1][2];
		m[1][2] = -in[0][0] * in[1][2] * in[3][3] + in[0][0] * in[1][3] * in[3][2] + in[1][0] * in[0][2] * in[3][3]
			- in[1][0] * in[0][3] * in[3][2] - in[3][0] * in[0][2] * in[1][3] + in[3][0] * in[0][3] * in[1][2];
		m[2][2] = in[0][0] * in[1][1] * in[3][3] - in[0][0] * in[1][3] * in[3][1] - in[1][0] * in[0][1] * in[3][3]
			+ in[1][0] * in[0][3] * in[3][1] + in[3][0] * in[0][1] * in[1][3] - in[3][0] * in[0][3] * in[1][1];
		m[3][2] = -in[0][0] * in[1][1] * in[3][2] + in[0][0] * in[1][2] * in[3][1] + in[1][0] * in[0][1] * in[3][2]
			- in[1][0] * in[0][2] * in[3][1] - in[3][0] * in[0][1] * in[1][2] + in[3][0] * in[0][2] * in[1][1];

		m[0][3] = -in[0][1] * in[1][2] * in[2][3] + in[0][1] * in[1][3] * in[2][2] + in[1][1] * in[0][2] * in[2][3]
			- in[1][1] * in[0][3] * in[2][2] - in[2][1] * in[0][2] * in[1][3] + in[2][1] * in[0][3] * in[1][2];
		m[1][3] = in[0][0] * in[1][2] * in[2][3] - in[0][0] * in[1][3] * in[2][2] - in[1][0] * in[0][2] * in[2][3]
			+ in[1][0] * in[0][3] * in[2][2] + in[2][0] * in[0][2] * in[1][3] - in[2][0] * in[0][3] * in[1][2];
		m[2][3] = -in[0][0] * in[1][1] * in[2][3] + in[0][0] * in[1][3] * in[2][1] + in[1][0] * in[0][1] * in[2][3]
			- in[1][0] * in[0][3] * in[2][1] - in[2][0] * in[0][1] * in[1][3] + in[2][0] * in[0][3] * in[1][1];
		m[3][3] = in[0][0] * in[1][1] * in[2][2] - in[0][0] * in[1][2] * in[2][1] - in[1][0] * in[0][1] * in[2][2]
			+ in[1][0] * in[0][2] * in[2][1] + in[2][0] * in[0][1] * in[1][2] - in[2][0] * in[0][2] * in[1][1];

		float det = in[0].Dot(m.Row(0));

		if (det == 0)
		{
			return false;
		}

		det = 1.0f / det;
		out = m * det;

		return true;
	}

	Matrix4x4 Matrix4x4::Scale(const Vector3f& scale)
	{
		return Matrix4x4(Vector4f(scale.x, 0, 0, 0),
			Vector4f(0, scale.y, 0, 0),
			Vector4f(0, 0, scale.z, 0),
			Vector4f(0, 0, 0, 1));
	}

	Matrix4x4 Matrix4x4::Scale(float scale)
	{
		return Scale(Vector3f(scale, scale, scale));
	}

	Matrix4x4 Matrix4x4::Transpose() const
	{
		Vector4f r0 = m[0];
		Vector4f r1 = m[1];
		Vector4f r2 = m[2];
		Vector4f r3 = m[3];

		return Matrix4x4(Vector4f(r0.x, r1.x, r2.x, r3.x),
			Vector4f(r0.y, r1.y, r2.y, r3.y),
			Vector4f(r0.z, r1.z, r2.z, r3.z),
			Vector4f(r0.w, r1.w, r2.w, r3.w));
	}

	void Matrix4x4::ClipProjection(const Vector4f& clipPlane)
	{
		Vector4f q = Inverse() * Vector4f(Math::Sign(clipPlane.x), Math::Sign(clipPlane.y), 1.0f, 1.0f);
		Vector4f c = clipPlane * (2.0f / (clipPlane.Dot(q)));

		m[0][2] = c.x - m[0][3];
		m[1][2] = c.y - m[1][3];
		m[2][2] = c.z - m[2][3];
		m[3][2] = c.w - m[3][3];
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const
	{
		return Matrix4x4(
			m[0][0] * rhs[0][0] + m[1][0] * rhs[0][1] + m[2][0] * rhs[0][2] + m[3][0] * rhs[0][3],
			m[0][1] * rhs[0][0] + m[1][1] * rhs[0][1] + m[2][1] * rhs[0][2] + m[3][1] * rhs[0][3],
			m[0][2] * rhs[0][0] + m[1][2] * rhs[0][1] + m[2][2] * rhs[0][2] + m[3][2] * rhs[0][3],
			m[0][3] * rhs[0][0] + m[1][3] * rhs[0][1] + m[2][3] * rhs[0][2] + m[3][3] * rhs[0][3],

			m[0][0] * rhs[1][0] + m[1][0] * rhs[1][1] + m[2][0] * rhs[1][2] + m[3][0] * rhs[1][3],
			m[0][1] * rhs[1][0] + m[1][1] * rhs[1][1] + m[2][1] * rhs[1][2] + m[3][1] * rhs[1][3],
			m[0][2] * rhs[1][0] + m[1][2] * rhs[1][1] + m[2][2] * rhs[1][2] + m[3][2] * rhs[1][3],
			m[0][3] * rhs[1][0] + m[1][3] * rhs[1][1] + m[2][3] * rhs[1][2] + m[3][3] * rhs[1][3],

			m[0][0] * rhs[2][0] + m[1][0] * rhs[2][1] + m[2][0] * rhs[2][2] + m[3][0] * rhs[2][3],
			m[0][1] * rhs[2][0] + m[1][1] * rhs[2][1] + m[2][1] * rhs[2][2] + m[3][1] * rhs[2][3],
			m[0][2] * rhs[2][0] + m[1][2] * rhs[2][1] + m[2][2] * rhs[2][2] + m[3][2] * rhs[2][3],
			m[0][3] * rhs[2][0] + m[1][3] * rhs[2][1] + m[2][3] * rhs[2][2] + m[3][3] * rhs[2][3],

			m[0][0] * rhs[3][0] + m[1][0] * rhs[3][1] + m[2][0] * rhs[3][2] + m[3][0] * rhs[3][3],
			m[0][1] * rhs[3][0] + m[1][1] * rhs[3][1] + m[2][1] * rhs[3][2] + m[3][1] * rhs[3][3],
			m[0][2] * rhs[3][0] + m[1][2] * rhs[3][1] + m[2][2] * rhs[3][2] + m[3][2] * rhs[3][3],
			m[0][3] * rhs[3][0] + m[1][3] * rhs[3][1] + m[2][3] * rhs[3][2] + m[3][3] * rhs[3][3]
		);
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix3x3& rhs) const
	{
		return *this * rhs.ToMatrix4x4();
	}

	void Matrix4x4::operator*=(const Matrix4x4& rhs)
	{
		*this = *this * rhs;
	}

	Vector4f Matrix4x4::operator*(const Vector4f& rhs) const
	{
		return Transform(rhs);
	}

	Vector3f Matrix4x4::operator*(const Vector3f& rhs) const
	{
		return Transform(rhs) + m[3].xyz();
	}

	Matrix4x4 Matrix4x4::operator*(float rhs) const
	{
		Matrix4x4 r = *this;

		r.m[0] *= rhs;
		r.m[1] *= rhs;
		r.m[2] *= rhs;
		r.m[3] *= rhs;

		return r;
	}

	const float* Matrix4x4::Base() const
	{
		return m[0].Base();
	}

	float* Matrix4x4::Base()
	{
		return m[0].Base();
	}
}
