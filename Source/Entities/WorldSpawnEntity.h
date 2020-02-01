#pragma once

#include "BrushModelEntity.h"

namespace Freeking
{
	class WorldSpawnEntity : public BrushModelEntity
	{
	public:

		virtual std::shared_ptr<BrushModel> GetModel() override final;
	};
}
