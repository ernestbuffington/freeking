#include "BaseWorldEntity.h"
#include "Map.h"
#include "Util.h"

namespace Freeking
{
	BaseWorldEntity::BaseWorldEntity() : BaseEntity()
	{
	}

	void BaseWorldEntity::InitializeProperties(const EntityLump::EntityDef& def)
	{
		BaseEntity::InitializeProperties(def);

		if (!def.logic)
		{
			Vector3f origin(def.origin.x, def.origin.z, -def.origin.y);
			Quaternion rotation = Quaternion(0, 0, 0, 1);

			if (def.angle > 0)
			{
				rotation = Quaternion::FromDegreeAngles(Vector3f(0, def.angle, 0));
			}

			SetPosition(origin);
			SetRotation(rotation);
		}
	}

	void BaseWorldEntity::Initialize()
	{
		BaseEntity::Initialize();
	}

	void BaseWorldEntity::PostInitialize()
	{
		BaseEntity::PostInitialize();
	}

	void BaseWorldEntity::Tick(double dt)
	{
		BaseEntity::Tick(dt);
	}

	void BaseWorldEntity::PostTick()
	{
		BaseEntity::PostTick();

		UpdateTransform();
	}

	void BaseWorldEntity::Spawn()
	{
		BaseEntity::Spawn();
	}

	void BaseWorldEntity::UpdateTransform()
	{
		_transform = Matrix4x4::Translation(_position) * _rotation.ToMatrix4x4();
	}
}
