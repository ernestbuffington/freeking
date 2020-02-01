#include "ButtonEntity.h"
#include "Map.h"

namespace Freeking
{
	ButtonEntity::ButtonEntity() : BrushModelEntity(),
		_speed(500.0f),
		_angle(0.0f),
		_lip(0.0f),
		_time(0.0f)
	{
	}

	void ButtonEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		auto rotation = Quaternion::FromDegreeYaw(_angle);

		float distance = 0.0f;
		if (_model)
		{
			auto extent = rotation * (GetLocalMaxBounds() - GetLocalMinBounds());
			distance = _lip - extent.x;
		}

		_time = Math::Mod(_time + (float)(dt * Math::DegreesToRadians(_speed)), Math::TwoPi);
		auto direction = rotation * Vector3f(1, 0, 0);
		distance *= Math::Clamp((Math::Sin(_time) + 1.0f) * 0.5f, 0.0f, 1.0f);
		SetPosition(_initialPosition + (direction.Normalise() * distance));
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
