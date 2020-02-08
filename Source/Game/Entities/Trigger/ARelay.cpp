#include "ARelay.h"
#include "TimeUtil.h"

namespace Freeking::Entity::Trigger
{
	ARelay::ARelay() : BaseEntity(),
		_delay(0.0f),
		_timeToTrigger(0.0),
		_triggered(false)
	{
	}

	void ARelay::Tick(double dt)
	{
		if (_triggered && _timeToTrigger < Time::Now())
		{
			_triggered = false;
			_timeToTrigger = 0.0;

			TriggerTarget();
		}
	}

	void ARelay::Trigger()
	{
		_triggered = true;
		_timeToTrigger = Time::Now() + _delay;
	}

	bool ARelay::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("delay"))
		{
			return property.ValueAsFloat(_delay);
		}

		return BaseEntity::SetProperty(property);
	}
}
