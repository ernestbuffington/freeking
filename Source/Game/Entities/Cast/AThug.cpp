#include "AThug.h"

namespace Freeking::Entity::Cast
{
	AThug::AThug() : BaseCastEntity()
	{
		_modelFolder = "models/actors/thug";
		_skinFolder = { "models/actors/thug", "models/actors/thug", "models/actors/thug" };
	}
}
