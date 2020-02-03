#include "ButtonEntity.h"
#include "Map.h"
#include "TimeUtil.h"

namespace Freeking
{
	ButtonEntity::ButtonEntity() : BrushModelEntity(),
		_speed(40.0f),
		_angle(0.0f),
		_lip(4.0f),
		_moveDistance(0.0f)
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

		SetPosition(_initialPosition.MulAdd(_moveDistance * Math::SineWave(Time::Now() - _timeSpawned, _speed), _moveDirection));
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
