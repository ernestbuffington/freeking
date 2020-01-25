#include "IEntity.h"
#include "Map.h"
#include "Util.h"

namespace Freeking
{
	BaseEntity::BaseEntity() :
		_map(nullptr),
		_position(0),
		_rotation(0, 0, 0, 1)
	{
	}

	void BaseEntity::Tick(double dt)
	{
		_transform = Matrix4x4::Translation(_position) * _rotation.ToMatrix4x4();
	}

	BrushModelEntity::BrushModelEntity() :
		_modelIndex(-1)
	{
	}

	void BrushModelEntity::Tick(double dt)
	{
		BaseEntity::Tick(dt);
	}

	void BrushModelEntity::Initialize()
	{
		if (_modelIndex < 0)
		{
			return;
		}

		_model = _map->GetBrushModel(_modelIndex);
	}

	void BrushModelEntity::RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader)
	{
		if (_model)
		{
			_model->RenderOpaque(viewProjection, shader);
		}
	}

	void BrushModelEntity::RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader)
	{
		if (_model)
		{
			_model->RenderTranslucent(viewProjection, shader);
		}
	}

	bool BrushModelEntity::SetProperty(const EntityKeyValue& keyValue)
	{
		if (keyValue.Key == "model" &&
			!keyValue.Value.empty() &&
			keyValue.Value[0] == '*')
		{
			return Util::TryParseInt(keyValue.Value.substr(1), _modelIndex);
		}

		return false;
	}

	void WorldSpawnEntity::Initialize()
	{
		_modelIndex = 0;
		BrushModelEntity::Initialize();
	}

	RotatingEntity::RotatingEntity() :
		_speed(0.0f)
	{
	}

	void RotatingEntity::Tick(double dt)
	{
		_rotation *= Quaternion::FromDegreeAngles(Vector3f(0, _speed * dt, 0));

		BrushModelEntity::Tick(dt);
	}

	bool RotatingEntity::SetProperty(const EntityKeyValue& keyValue)
	{
		if (keyValue.Key == "speed")
		{
			return keyValue.ValueAsFloat(_speed);
		}

		return BrushModelEntity::SetProperty(keyValue);
	}

	DoorRotatingEntity::DoorRotatingEntity() :
		_speed(100.0f),
		_angle(0.0f),
		_distance(0.0f),
		_time(0.0f)
	{
	}

	void DoorRotatingEntity::Tick(double dt)
	{
		BrushModelEntity::Tick(dt);

		_time += (dt * Math::DegreesToRadians(_speed));
		_time = std::fmodf(_time, Math::TWO_PI);

		float t = (std::sinf(_time) + 1.0f) * 0.5f;

		_rotation = Quaternion::FromDegreeAngles(Vector3f(0, _distance * (t * -1.0f), 0));
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
			_rotation = Quaternion(0, 0, 0, 1);
			return keyValue.ValueAsFloat(_angle);
		}

		return BrushModelEntity::SetProperty(keyValue);
	}

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

		_position = _initialPosition + Vector3f(0, distance * (t * 1.0f), 0);
	}

	bool DoorEntity::SetProperty(const EntityKeyValue& keyValue)
	{
		if (keyValue.Key == "speed")
		{
			return keyValue.ValueAsFloat(_speed);
		}
		else if (keyValue.Key == "angle")
		{
			_rotation = Quaternion(0, 0, 0, 1);
			return keyValue.ValueAsFloat(_angle);
		}

		return BrushModelEntity::SetProperty(keyValue);
	}
}
