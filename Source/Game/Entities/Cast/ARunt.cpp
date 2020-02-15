#include "ARunt.h"

namespace Freeking::Entity::Cast
{
	ARunt::ARunt() : BaseCastEntity()
	{
		_modelFolder = "models/actors/runt";
		_skinFolder = { "models/actors/runt", "models/actors/runt", "models/actors/thug" };
	}
}
