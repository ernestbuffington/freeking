#include "FreeCamera.h"
#include "Matrix3x3.h"

namespace Freeking
{
	FreeCamera::FreeCamera() :
		_position(0.0f, 0.0f, 0.0f)
	{
		SetRotation(0.0f, 0.0f, 0.0f);
		UpdateTransform();
	}

	void FreeCamera::MoveTo(const Vector3f& position)
	{
		_position = position;
		UpdateTransform();
	}

	void FreeCamera::Move(const Vector3f& force, float dt)
	{
		if (force.Length() > 0.0f)
		{
			_position -= (_rotation * force) * dt;
			UpdateTransform();
		}
	}

	void FreeCamera::LookDelta(float x, float y)
	{
		SetRotation(_pitch - y, _yaw - x, _roll);
		UpdateTransform();
	}

	void FreeCamera::UpdateTransform()
	{
		_transform = _rotation.Inverse().ToMatrix4x4() * Matrix4x4::Translation(_position * -1.0f);
	}

	void FreeCamera::SetRotation(float pitch, float yaw, float roll)
	{
		_pitch = Math::Clamp(pitch, -90.0f, 90.0f);
		_yaw = fmod(yaw + (ceil(-yaw / 360.0f) * 360.0f), 360.0f);
		_roll = fmod(roll + (ceil(-roll / 360.0f) * 360.0f), 360.0f);
		_rotation = Quaternion::FromDegreeAngles(_pitch, _yaw, _roll);
	}

	Vector3f FreeCamera::NormalisedScreenPointToDirection(const Matrix4x4& projection, const Vector2f& point) const
	{
		Vector3f v;
		v.x = point.x / projection[0][0];
		v.y = point.y / projection[1][1];
		v.z = -1.0f;

		return  _rotation * v;
	}
}
