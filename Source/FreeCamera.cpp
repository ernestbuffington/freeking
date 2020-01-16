#include "FreeCamera.h"
#include "Matrix3x3.h"

namespace Freeking
{
	FreeCamera::FreeCamera() :
		Pitch(0.0f), Yaw(0.0f), Position(0.0f, 0.0f, 0.0f)
	{
		UpdateRotationQuat();
		UpdateViewMatrix();
	}

	void FreeCamera::MoveTo(const Vector3f& position)
	{
		Position = position;
		UpdateViewMatrix();
	}

	void FreeCamera::Move(const Vector3f& force, float dt)
	{
		if (force.Length() > 0.0f)
		{
			Position -= (RotationQuat.Inverse() * force) * dt;
			UpdateViewMatrix();
		}
	}

	void FreeCamera::LookDelta(float x, float y)
	{
		Yaw += -x;
		Yaw += ceil(-Yaw / 360.0f) * 360.0f;
		Pitch = Math::Clamp(Pitch + -y, -90.0f, 90.0f);

		UpdateRotationQuat();
		UpdateViewMatrix();
	}

	void FreeCamera::UpdateViewMatrix()
	{
		ViewMatrix = RotationQuat.ToMatrix4x4() * Matrix4x4::Translation(-Position);
	}

	void FreeCamera::UpdateRotationQuat()
	{
		RotationQuat = Quaternion::FromDegreeAngles(Vector3f(Pitch, Yaw, 0.0)).Inverse();
	}
}
