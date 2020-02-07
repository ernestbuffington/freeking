#include "AWall.h"

namespace Freeking::Entity::Func
{
	AWall::AWall() : BrushModelEntity(),
		_spawnFlags(SpawnFlags::None)
	{
	}

	void AWall::Initialize()
	{
		BrushModelEntity::Initialize();

		_hidden = _spawnFlags[SpawnFlags::TriggerSpawn];
	}

	void AWall::OnTrigger()
	{
		if (_spawnFlags[SpawnFlags::TriggerSpawn] && _hidden)
		{
			_hidden = false;
		}
	}

	bool AWall::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("spawnflags"))
		{
			return property.ValueAsFlags(_spawnFlags);
		}

		return BrushModelEntity::SetProperty(property);
	}
}
