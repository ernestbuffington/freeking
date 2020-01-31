#include "BaseWorldEntity.h"
#include "EntityComponent.h"
#include "Map.h"
#include "Util.h"

namespace Freeking
{
	BaseWorldEntity::BaseWorldEntity() : BaseEntity(),
		_rootComponent(CreateComponent<SceneComponent>())
	{
	}

	void BaseWorldEntity::Initialize()
	{
	}

	void BaseWorldEntity::Tick(double dt)
	{
	}

	void BaseWorldEntity::InitializeProperties(const EntityLump::EntityDef& def)
	{
		IEntity::InitializeProperties(def);

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
}
