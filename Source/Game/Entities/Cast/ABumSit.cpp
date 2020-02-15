#include "ABumSit.h"

namespace Freeking::Entity::Cast
{
	ABumSit::ABumSit() : BaseCastEntity()
	{
		_modelFolder = "models/actors/bum_sit";
		_skinFolder = { "models/actors/thug", "models/actors/thug", "models/actors/thug" };
	}
}
