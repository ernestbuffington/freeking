#pragma once

#include "BrushModelEntity.h"

namespace Freeking
{
	class ButtonEntity : public BrushModelEntity
	{
	public:

		ButtonEntity();

		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

		virtual void InitializeAngleProperty(float angle) override;

	private:

		float _speed;
		float _angle;
		float _lip;
		float _time;
		Vector3f _initialPosition;
	};

}
