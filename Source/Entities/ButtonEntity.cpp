#include "ButtonEntity.h"
#include "Map.h"
#include "TimeUtil.h"
#include "Audio/AudioDevice.h"
#include "Audio/AudioClip.h"

namespace Freeking
{
	ButtonEntity::ButtonEntity() : BrushModelEntity(),
		_speed(40.0f),
		_angle(0.0f),
		_lip(4.0f),
		_moveDistance(0.0f),
		_currentDistance(0.0f),
		_timeToUnpress(0.0),
		_pressed(false)
	{
	}

	void ButtonEntity::Initialize()
	{
		BrushModelEntity::Initialize();

		_initialPosition = GetPosition();

		auto yaw = Quaternion::FromDegreeYaw(_angle);
		_moveDistance = _lip - (yaw * (GetLocalMaxBounds() - GetLocalMinBounds())).x;
		_moveDirection = (yaw * Vector3f::OneX).Normalise();
	}

	void ButtonEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		if (_pressed && Time::Now() >= _timeToUnpress)
		{
			_pressed = false;
		}

		_currentDistance += ((_speed * (float)dt) * (_pressed ? 1.0f : -1.0f));
		_currentDistance = Math::Clamp(_currentDistance, 0.0f, _moveDistance);

		SetPosition(_initialPosition.MulAdd(_currentDistance, _moveDirection));
	}

	void ButtonEntity::OnTrigger()
	{
		if (_pressed)
		{
			return;
		}

		_pressed = true;
		_timeToUnpress = Time::Now() + 3.0;

		AudioDevice::Current->Play(AudioClip::Library.Get("sound/world/switches/wheel.wav").get(), GetTransformCenter().Translation());
	}

	bool ButtonEntity::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("lip"))
		{
			return property.ValueAsFloat(_lip);
		}

		return BrushModelEntity::SetProperty(property);
	}

	void ButtonEntity::InitializeAngleProperty(float angle)
	{
		// "angle" for this entity is used for direction and not entity rotation
		_angle = angle;
	}
}
