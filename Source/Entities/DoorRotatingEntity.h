#pragma once

#include "BrushModelEntity.h"

namespace Freeking
{
	class DoorRotatingEntity : public BrushModelEntity
	{
	public:

		DoorRotatingEntity();

		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

	private:

		float _speed;
		float _angle;
		float _distance;
		float _time;
	};

}
