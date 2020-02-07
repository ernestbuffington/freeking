#include "BaseEntity.h"
#include "TimeUtil.h"
#include "Map.h"

namespace Freeking
{
	BaseEntity::BaseEntity() :
		_timeSpawned(0)
	{
	}

	void BaseEntity::InitializeProperties(const EntityProperties& properties)
	{
		if (const auto& name = properties.GetNameProperty()) _name = name;
		if (const auto& classname = properties.GetClassnameProperty()) _classname = classname;
		if (const auto& targetname = properties.GetTargetnameProperty()) _targetname = targetname;
		if (const auto& target = properties.GetTargetProperty()) _target = target;

		for (const auto& property : properties.GetKeyValues())
		{
			SetProperty(property);
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
		_timeSpawned = Time::Now();
	}

	void BaseEntity::Trigger()
	{
		OnTrigger();

		if (!_target.empty())
		{
			for (const auto& targetEntity : Map::Current->GetTargetEntities(_target))
			{
				targetEntity->Trigger();
			}
		}
	}

	void BaseEntity::OnTrigger()
	{
	}

	bool BaseEntity::SetProperty(const EntityProperty& property)
	{
		return false;
	}
}
