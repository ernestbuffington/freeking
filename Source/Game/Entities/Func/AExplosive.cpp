#include "AExplosive.h"

namespace Freeking::Entity::Func
{
	AExplosive::AExplosive() : BrushModelEntity(),
		_spawnFlags(SpawnFlags::None)
	{
	}

	bool AExplosive::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("spawnflags"))
		{
			return property.ValueAsFlags(_spawnFlags);
		}

		return BrushModelEntity::SetProperty(property);
	}
}
