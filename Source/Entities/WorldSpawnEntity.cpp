#include "WorldSpawnEntity.h"
#include "Map.h"

namespace Freeking
{
	std::shared_ptr<BrushModel> WorldSpawnEntity::GetModel()
	{
		return Map::Current->GetBrushModel(0);
	}
}
