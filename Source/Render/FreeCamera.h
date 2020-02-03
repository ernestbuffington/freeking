#pragma once

#include "Vector.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

namespace Freeking
{
	class FreeCamera
	{
	public:

		FreeCamera();

		inline const Vector3f& GetPosition() const { return Position; }
		inline const Quaternion& GetRotation() const { return RotationQuat; }
		inline const Matrix4x4& GetViewMatrix() const { return ViewMatrix; }
		inline const float GetPitch() const { return Pitch; }
		inline const float GetYaw() const { return Yaw; }

		void MoveTo(const Vector3f& position);
		void Move(const Vector3f& force, float dt);
		void LookDelta(float x, float y);

	private:

		void UpdateViewMatrix();
		void UpdateRotationQuat();

		float Pitch;
		float Yaw;

		Vector3f Position;
		Quaternion RotationQuat;
		Matrix4x4 ViewMatrix;
	};
}
