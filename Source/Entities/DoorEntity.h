#pragma once

#include "BrushModelEntity.h"

namespace Freeking
{
	class DoorEntity : public BrushModelEntity
	{
	public:

		DoorEntity();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

	private:

		float _speed;
		float _angle;
		float _time;
		float _distance;
		Vector3f _initialPosition;
	};
}
