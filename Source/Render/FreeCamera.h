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

		inline const Vector3f& GetPosition() const { return _position; }
		inline const Quaternion& GetRotation() const { return _rotation; }
		inline const Matrix4x4& GetTransform() const { return _transform; }
		inline const float GetPitch() const { return _pitch; }
		inline const float GetYaw() const { return _yaw; }
		inline const float GetRoll() const { return _roll; }

		void MoveTo(const Vector3f& position);
		void Move(const Vector3f& force, float dt);
		void LookDelta(float x, float y);

		Vector3f NormalisedScreenPointToDirection(const Matrix4x4& projection, const Vector2f& point) const;

	private:

		void UpdateTransform();
		void SetRotation(float pitch, float yaw, float roll);

		void ApplyGravity(double dt);
		void ApplyFriction(double friction, double dt);
		void ApplyAcceleration(const Vector3f& wishDirection, double wishSpeed, double acceleration, double dt);

		void FlyMove(const Vector3f& force, float dt);

		float _pitch;
		float _yaw;
		float _roll;

		Vector3f _position;
		Quaternion _rotation;
		Matrix4x4 _transform;

		Vector3f _movementPosition;
		Vector3f _movementVelocity;
		bool _noclip;
	};
}
