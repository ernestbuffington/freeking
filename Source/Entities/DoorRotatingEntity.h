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

		void Open();
		void Close();

		virtual void OnTrigger() override;

		virtual bool SetProperty(const EntityProperty& property) override;

		virtual void InitializeAngleProperty(float angle) override;

	private:

		float _speed;
		float _angle;
		float _distance;
		float _wait;

		float _currentDistance;
		double _timeToClose;
		bool _open;
	};

}
