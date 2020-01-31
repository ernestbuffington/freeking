#pragma once

#include "BrushModelEntity.h"

namespace Freeking
{
	class RotatingEntity : public BrushModelEntity
	{
	public:

		RotatingEntity();

		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

	private:

		float _speed;
	};
}
