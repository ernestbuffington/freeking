#include "RotatingEntity.h"

namespace Freeking
{
	RotatingEntity::RotatingEntity() : BrushModelEntity(),
		_speed(0.0f)
	{
	}

	void RotatingEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		AddRotation(Quaternion::FromDegreeAngles(Vector3f(0, _speed * dt, 0)));
	}

	bool RotatingEntity::SetProperty(const EntityKeyValue& keyValue)
	{
		if (keyValue.Key == "speed")
		{
			return keyValue.ValueAsFloat(_speed);
		}

		return BrushModelEntity::SetProperty(keyValue);
	}
}
