#include "SceneEntity.h"
#include "Map.h"
#include "Util.h"

namespace Freeking
{
	SceneEntity::SceneEntity() : BaseEntity()
	{
	}

	void SceneEntity::InitializeProperties(const EntityLump::EntityDef& def)
	{
		BaseEntity::InitializeProperties(def);

		SetPosition(Vector3f(def.origin.x, def.origin.z, -def.origin.y));
		SetRotation(Quaternion::FromDegreeAngles(Vector3f(0, def.angle, 0)));
	}

	void SceneEntity::Initialize()
	{
		BaseEntity::Initialize();
	}

	void SceneEntity::PostInitialize()
	{
		BaseEntity::PostInitialize();
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

	bool SceneEntity::SetProperty(const EntityKeyValue& keyValue)
	{
		return false;
	}

	void SceneEntity::UpdateTransform()
	{
		_transform = Matrix4x4::Translation(_position) * _rotation.ToMatrix4x4();
	}
}
