#include "DoorEntity.h"
#include "Map.h"

namespace Freeking
{
	DoorEntity::DoorEntity() : BrushModelEntity(),
		_speed(100.0f),
		_angle(0.0f),
		_time(0.0f),
		_distance(0.0f)
	{
	}

	void DoorEntity::Initialize()
	{
		BrushModelEntity::Initialize();

		if (_model)
		{
			_distance = (_model->BoundsMax - _model->BoundsMin).y - 8.0f;
		}
	}

	void DoorEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		_time = Math::Mod(_time + ((float)dt * Math::DegreesToRadians(_speed)), Math::TwoPi);
		SetPosition(_initialPosition + Vector3f(0, _distance * ((Math::Sin(_time) + 1.0f) * 0.5f), 0));
	}

	bool DoorEntity::SetProperty(const EntityKeyValue& keyValue)
	{
		if (keyValue.Key == "speed")
		{
			return keyValue.ValueAsFloat(_speed);
		}
		else if (keyValue.Key == "angle")
		{
			SetRotation(Quaternion(0, 0, 0, 1));
			return keyValue.ValueAsFloat(_angle);
		}

		return BrushModelEntity::SetProperty(keyValue);
	}
}
