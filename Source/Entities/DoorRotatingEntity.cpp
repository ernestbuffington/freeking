#include "DoorRotatingEntity.h"
#include "TimeUtil.h"

namespace Freeking
{
	DoorRotatingEntity::DoorRotatingEntity() : BrushModelEntity(),
		_speed(100.0f),
		_angle(0.0f),
		_distance(0.0f)
	{
	}

	void DoorRotatingEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		SetRotation(Quaternion::FromDegreeYaw(_distance * (Math::SineWave(Time::Now() - _timeSpawned, Math::DegreesToRadians(_speed)) * -1.0f)));
	}

	bool DoorRotatingEntity::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("speed"))
		{
			return property.ValueAsFloat(_speed);
		}
		else if (property.IsKey("distance"))
		{
			return property.ValueAsFloat(_distance);
		}

		return BrushModelEntity::SetProperty(property);
	}

	void DoorRotatingEntity::InitializeAngleProperty(float angle)
	{
		// "angle" for this entity is used for direction and not entity rotation
		_angle = angle;
	}
}
