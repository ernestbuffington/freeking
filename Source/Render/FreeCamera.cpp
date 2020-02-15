#include "FreeCamera.h"
#include "Matrix3x3.h"
#include "Map.h"
#include "Input.h"
#include "Util.h"
#include "Audio/AudioDevice.h"
#include "Audio/AudioClip.h"

namespace Freeking
{
	static const float Speed = 300.0f;
	static const float AirSpeed = 50.0f;
	static const float Acceleration = 10.0f;
	static const float AirAcceleration = 100.0f;
	static const float GroundFriction = 8.0f;
	static const float AirFriction = 0.0f;
	static const float Gravity = 1000.0f;
	static const float JumpHeight = 45.0f;

	FreeCamera::FreeCamera() :
		_position(0),
		_movementPosition(0),
		_movementVelocity(0),
		_noclip(false)
	{
		SetRotation(0.0f, 0.0f, 0.0f);
		UpdateTransform();
	}

	void FreeCamera::MoveTo(const Vector3f& position)
	{
		_movementPosition = position;
		UpdateTransform();
	}

	static float CalculateEyeRoll(const Vector3f& velocity, const Vector3f& right, float rollSpeed, float rollAngle)
	{
		float side = Vector3f::Dot(velocity, right);
		float sign = side < 0.0f? -1.0f : 1.0f;
		side = fabs(side);

		if (side < rollSpeed)
		{
			side *= rollAngle / rollSpeed;
		}
		else
		{
			side = rollAngle;
		}

		return side * sign;
	}

	void FreeCamera::Move(const Vector3f& force, float dt)
	{
		if (Input::JustPressed(Button::KeyV))
		{
			_noclip = !_noclip;
		}

		if (_noclip)
		{
			FlyMove(force, dt);

			return;
		}

		Vector3f mins(-16, -16, -72);
		Vector3f maxs(16, 16, 0);

		bool isGrounded = false;
		bool isWalking = false;
		TraceResult trace = Map::Current->BoxTrace(_movementPosition, _movementPosition + (Vector3f::Down * 0.25f), mins, maxs, BspContentFlags::MaskPlayerSolid);

		if (trace.hit)
		{
			isGrounded = true;

			if (trace.planeNormal[1] > 0.7f)
			{
				isWalking = true;
			}
		}

		Quaternion yawRotation = Quaternion::FromDegreeYaw(_yaw);
		Vector3f forward = yawRotation.Forward().Normalise();
		Vector3f right = yawRotation.Right().Normalise();

		if (isWalking)
		{
			forward.ProjectOntoPlane(trace.planeNormal.Normalise(), 1.001f);
			right.ProjectOntoPlane(trace.planeNormal.Normalise(), 1.001f);

			forward = forward.Normalise();
			right = right.Normalise();
		}

		Vector3f wishDirection = forward * force.z + right * force.x;

		if (wishDirection.SquaredLength() > 0)
		{
			wishDirection = wishDirection.Normalise();
		}

		ApplyFriction(isWalking ? GroundFriction : AirFriction, dt);
		ApplyAcceleration(wishDirection, isWalking ? Speed : AirSpeed, isWalking ? Acceleration : AirAcceleration, dt);

		if (isWalking && Input::IsDown(Button::KeySPACE))
		{
			_movementVelocity[1] = sqrt(2.0f * Gravity * JumpHeight);
			isGrounded = false;
			isWalking = false;

			AudioDevice::Current->Play(AudioClip::Library.Get("sound/actors/player/male/jump" + std::to_string(Util::RandomInt(1, 3)) + ".wav").get(), 0, false, true);
		}

		if (!isWalking)
		{
			ApplyGravity(dt);
		}

		Vector3f oldVelocity = _movementVelocity;

		if (isGrounded)
		{
			_movementVelocity.ProjectOntoPlane(trace.planeNormal, 1.001f);
		}

		Map::Current->SlideMove(dt, _movementPosition, _movementVelocity, mins, maxs, BspContentFlags::MaskPlayerSolid, !isWalking, isGrounded, trace.planeNormal);

		SetRotation(_pitch, _yaw, CalculateEyeRoll(_movementVelocity, yawRotation.Right(), 500.0f, 4.0f));

		UpdateTransform();
	}

	void FreeCamera::FlyMove(const Vector3f& force, float dt)
	{
		_movementVelocity = (_rotation * (force * -1.0f));
		_movementPosition += _movementVelocity * dt;
		UpdateTransform();
	}

	void FreeCamera::LookDelta(float x, float y)
	{
		SetRotation(_pitch - y, _yaw - x, _roll);
		UpdateTransform();
	}

	void FreeCamera::UpdateTransform()
	{
		_position = _movementPosition + Vector3f(0, -10, 0);
		_transform = _rotation.Inverse().ToMatrix4x4() * Matrix4x4::Translation(_position * -1.0f);
	}

	void FreeCamera::SetRotation(float pitch, float yaw, float roll)
	{
		_pitch = Math::Clamp(pitch, -90.0f, 90.0f);
		_yaw = fmod(yaw + (ceil(-yaw / 360.0f) * 360.0f), 360.0f);
		_roll = fmod(roll + (ceil(-roll / 360.0f) * 360.0f), 360.0f);
		_rotation = Quaternion::FromDegreeYaw(_yaw) * Quaternion::FromDegreePitch(_pitch) * Quaternion::FromDegreeRoll(_roll);
	}

	void FreeCamera::ApplyGravity(double dt)
	{
		_movementVelocity += (Vector3f::Down * (Gravity * (float)dt));
	}

	void FreeCamera::ApplyFriction(float friction, double dt)
	{
		float speed = _movementVelocity.Length();
		float drop = speed * friction * (float)dt;
		float newSpeed = speed - drop;

		if (newSpeed < 0.0f)
		{
			newSpeed = 0.0f;
		}

		if (speed > 0.0f)
		{
			newSpeed /= speed;
		}

		_movementVelocity *= newSpeed;
	}

	void FreeCamera::ApplyAcceleration(const Vector3f& wishDirection, float wishSpeed, float acceleration, double dt)
	{
		float currentSpeed = Vector3f::Dot(wishDirection, _movementVelocity);
		float addSpeed = wishSpeed - currentSpeed;

		if (addSpeed <= 0.0)
		{
			return;
		}

		float accelerationSpeed = acceleration * (float)dt * wishSpeed;

		if (accelerationSpeed > addSpeed)
		{
			accelerationSpeed = addSpeed;
		}

		_movementVelocity += accelerationSpeed * wishDirection;
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
