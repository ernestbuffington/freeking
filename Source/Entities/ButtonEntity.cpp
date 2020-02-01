#include "ButtonEntity.h"
#include "Map.h"

namespace Freeking
{
	ButtonEntity::ButtonEntity() : BrushModelEntity(),
		_speed(500.0f),
		_angle(0.0f),
		_lip(0.0f),
		_time(0.0f),
		_moveDistance(0.0f)
	{
	}

	void ButtonEntity::Initialize()
	{
		BrushModelEntity::Initialize();

		_initialPosition = GetPosition();

		auto yaw = Quaternion::FromDegreeYaw(_angle);
		_moveDistance = _lip - (yaw * (GetLocalMaxBounds() - GetLocalMinBounds())).x;
		_moveDirection = (yaw * Vector3f(1, 0, 0)).Normalise();
	}

	void ButtonEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		_time = Math::Mod(_time + (float)(dt * Math::DegreesToRadians(_speed)), Math::TwoPi);
		SetPosition(_initialPosition + (_moveDirection * (_moveDistance * Math::SineWave(_time))));
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
