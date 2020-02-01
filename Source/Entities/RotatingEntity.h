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

		virtual bool SetProperty(const EntityProperty& property) override;

	private:

		float _speed;
	};
}
