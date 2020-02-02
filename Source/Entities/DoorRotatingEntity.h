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

		virtual bool SetProperty(const EntityProperty& property) override;

		virtual void InitializeAngleProperty(float angle) override;

	private:

		float _speed;
		float _angle;
		float _distance;
	};

}
