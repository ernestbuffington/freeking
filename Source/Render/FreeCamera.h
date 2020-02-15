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
		inline const Vector3f& GetViewModelOffset() const { return _viewModelOffset; }

		void MoveTo(const Vector3f& position);
		void Move(const Vector3f& force, float dt);
		void LookDelta(float x, float y);

		Vector3f NormalisedScreenPointToDirection(const Matrix4x4& projection, const Vector2f& point) const;

	private:

		void UpdateTransform();
		void SetRotation(float pitch, float yaw, float roll);

		void ApplyGravity(double dt);
		void ApplyFriction(float friction, double dt);
		void ApplyAcceleration(const Vector3f& wishDirection, float wishSpeed, float acceleration, double dt);

		void FlyMove(const Vector3f& force, float dt);

		Vector3f CalcSwingOffset(float pitchDelta, float yawDelta, double dt);

		float _pitch;
		float _yaw;
		float _roll;

		float _prevPitch;
		float _prevYaw;

		Vector3f _position;
		Quaternion _rotation;
		Matrix4x4 _transform;

		Vector3f _movementPosition;
		Vector3f _movementVelocity;
		bool _noclip;

		Vector3f _swingOffset;
		Vector3f _viewModelOffset;
		float _returnSpeed;
		float _swingInfluence;
		float _maxOffsetLength;
	};
}
