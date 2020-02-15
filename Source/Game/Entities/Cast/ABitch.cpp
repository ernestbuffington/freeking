#include "ABitch.h"

namespace Freeking::Entity::Cast
{
	ABitch::ABitch() : BaseCastEntity()
	{
		_modelFolder = "models/actors/bitch";
		_skinFolder = { "models/actors/bitch", "models/actors/bitch", "models/actors/bitch" };
	}
}
