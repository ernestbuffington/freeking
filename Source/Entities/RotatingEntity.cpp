#include "RotatingEntity.h"
#include "TimeUtil.h"

namespace Freeking
{
	RotatingEntity::RotatingEntity() : BrushModelEntity(),
		_speed(0.0f)
	{
	}

	void RotatingEntity::Initialize()
	{
		BrushModelEntity::Initialize();

		_initialRotation = GetRotation();
	}

	void RotatingEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		if (_speed > 0.0f)
		{
			SetRotation(_initialRotation * Quaternion::FromRadianYaw(Math::AngleAtTime(Math::DegreesToRadians(Time::Now() - _timeSpawned), _speed)));
		}
	}

	bool RotatingEntity::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("speed"))
		{
			return property.ValueAsFloat(_speed);
		}

		return BrushModelEntity::SetProperty(property);
	}
}
