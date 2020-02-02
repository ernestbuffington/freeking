#include "DoorEntity.h"
#include "Map.h"
#include "TimeUtil.h"

namespace Freeking
{
	DoorEntity::DoorEntity() : BrushModelEntity(),
		_speed(100.0f),
		_angle(0.0f),
		_distance(0.0f)
	{
	}

	void DoorEntity::Initialize()
	{
		BrushModelEntity::Initialize();

		_initialPosition = GetPosition();
		_distance = (GetLocalMaxBounds() - GetLocalMinBounds()).y - 8.0f;
	}

	void DoorEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		SetPosition(_initialPosition + Vector3f::Up * (_distance * Math::SineWave(Time::Now() - _timeSpawned, _speed)));
	}

	bool DoorEntity::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("speed"))
		{
			return property.ValueAsFloat(_speed);
		}

		return BrushModelEntity::SetProperty(property);
	}

	void DoorEntity::InitializeAngleProperty(float angle)
	{
		// "angle" for this entity is used for direction and not entity rotation
		_angle = angle;
	}
}
