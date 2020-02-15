#include "APunk.h"

namespace Freeking::Entity::Cast
{
	APunk::APunk() : BaseCastEntity()
	{
		_modelFolder = "models/actors/punk";
		_skinFolder = { "models/actors/thug", "models/actors/thug", "models/actors/thug" };
	}
}
