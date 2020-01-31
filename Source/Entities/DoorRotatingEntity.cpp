#include "DoorRotatingEntity.h"

namespace Freeking
{
	DoorRotatingEntity::DoorRotatingEntity() : BrushModelEntity(),
		_speed(100.0f),
		_angle(0.0f),
		_distance(0.0f),
		_time(0.0f)
	{
	}

	void DoorRotatingEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		_time = Math::Mod(_time + ((float)dt * Math::DegreesToRadians(_speed)), Math::TwoPi);
		SetRotation(Quaternion::FromDegreeYaw(_distance * (((Math::Sin(_time) + 1.0f) * 0.5f) * -1.0f)));
	}

	bool DoorRotatingEntity::SetProperty(const EntityKeyValue& keyValue)
	{
		if (keyValue.Key == "speed")
		{
			return keyValue.ValueAsFloat(_speed);
		}
		else if (keyValue.Key == "distance")
		{
			return keyValue.ValueAsFloat(_distance);
		}
		else if (keyValue.Key == "angle")
		{
			SetRotation(Quaternion(0, 0, 0, 1));
			return keyValue.ValueAsFloat(_angle);
		}

		return BrushModelEntity::SetProperty(keyValue);
	}
}
