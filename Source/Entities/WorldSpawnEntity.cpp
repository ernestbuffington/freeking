#include "WorldSpawnEntity.h"
#include "Map.h"

namespace Freeking
{
	void WorldSpawnEntity::Initialize()
	{
		_model = Map::Current->GetBrushModel(0);
	}
}
