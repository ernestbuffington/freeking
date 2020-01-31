#include "DoorEntity.h"
#include "Map.h"

namespace Freeking
{
	DoorEntity::DoorEntity() :
		_speed(100.0f),
		_angle(0.0f),
		_time(0.0f)
	{
	}

	void DoorEntity::Initialize()
	{
		BrushModelEntity::Initialize();
	}

	void DoorEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		_time += (dt * Math::DegreesToRadians(_speed));
		_time = std::fmodf(_time, Math::TWO_PI);

		float t = (std::sinf(_time) + 1.0f) * 0.5f;
		float distance = (_model->BoundsMax - _model->BoundsMin).y - 8.0f;

		SetPosition(_initialPosition + Vector3f(0, distance * (t * 1.0f), 0));
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
