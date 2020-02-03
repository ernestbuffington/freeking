#include "BaseEntity.h"
#include "TimeUtil.h"

namespace Freeking
{
	BaseEntity::BaseEntity() :
		_timeSpawned(0)
	{
	}

	void BaseEntity::InitializeProperties(const EntityProperties& properties)
	{
		if (auto name = properties.GetNameProperty())
		{
			_name = name;
		}

		if (auto classname = properties.GetClassnameProperty())
		{
			_classname = classname;
		}

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

	bool BaseEntity::SetProperty(const EntityProperty& property)
	{
		return false;
	}
}
