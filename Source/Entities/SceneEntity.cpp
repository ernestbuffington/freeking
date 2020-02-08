#include "SceneEntity.h"
#include "Map.h"
#include "Util.h"

namespace Freeking
{
	SceneEntity::SceneEntity() : BaseEntity()
	{
	}

	void SceneEntity::InitializeProperties(const EntityProperties& properties)
	{
		BaseEntity::InitializeProperties(properties);

		if (const auto& origin = properties.GetOriginProperty())
		{
			InitializeOriginProperty(origin);
		}

		if (const auto& angle = properties.GetAngleProperty())
		{
			InitializeAngleProperty(angle);
		}
	}

	void SceneEntity::InitializeOriginProperty(const Vector3f& origin)
	{
		SetPosition(Util::ConvertVector(origin));
	}

	void SceneEntity::InitializeAngleProperty(float angle)
	{
		SetRotation(Quaternion::FromDegreeYaw(angle));
	}

	void SceneEntity::Initialize()
	{
		BaseEntity::Initialize();
	}

	void SceneEntity::PostInitialize()
	{
		BaseEntity::PostInitialize();

		UpdateTransform();
	}

	void SceneEntity::Tick(double dt)
	{
		BaseEntity::Tick(dt);
	}

	void SceneEntity::PostTick()
	{
		BaseEntity::PostTick();

		UpdateTransform();
	}

	void SceneEntity::Spawn()
	{
		BaseEntity::Spawn();
	}

	bool SceneEntity::SetProperty(const EntityProperty& property)
	{
		return false;
	}

	void SceneEntity::UpdateTransform()
	{
		_transform = Matrix4x4::Translation(_position) * _rotation.ToMatrix4x4();
		_transformCenter = _transform * Matrix4x4::Translation(_localBoundsCenter);
	}

	void SceneEntity::SetLocalBounds(const Vector3f& minBounds, const Vector3f& maxBounds)
	{
		_localMinBounds = minBounds;
		_localMaxBounds = maxBounds;
		_localBoundsCenter = _localMinBounds + ((_localMaxBounds - _localMinBounds) * 0.5f);
	}
}
