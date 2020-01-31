#include "IEntity.h"
#include "EntityComponent.h"

namespace Freeking
{
	void IEntity::InitializeProperties(const EntityLump::EntityDef& def)
	{
		_name = def.name;

		for (const auto& [key, value] : def.keyValues)
		{
			SetProperty({ key, value });
		}
	}

	void IEntity::Initialize()
	{
	}

	void IEntity::PostInitialize()
	{
		for (auto& component : _components)
		{
			component->PostInitialize();
		}
	}

	void IEntity::Tick(double dt)
	{
	}

	void IEntity::PostTick()
	{
		for (auto& component : _components)
		{
			component->PostTick();
		}
	}

	void IEntity::Spawn()
	{
	}
}
