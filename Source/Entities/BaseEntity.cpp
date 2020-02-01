#include "BaseEntity.h"

namespace Freeking
{
	void BaseEntity::InitializeProperties(const EntityLump::EntityDef& def)
	{
		_name = def.name;

		for (const auto& [key, value] : def.keyValues)
		{
			SetProperty({ key, value });
		}
	}

	void BaseEntity::Initialize()
	{
	}

	void BaseEntity::PostInitialize()
	{
	}

	void BaseEntity::Tick(double dt)
	{
	}

	void BaseEntity::PostTick()
	{
	}

	void BaseEntity::Spawn()
	{
	}
}
