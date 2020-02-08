#include "ATimer.h"
#include "TimeUtil.h"
#include "Util.h"
#include <iostream>

namespace Freeking::Entity::Func
{
	ATimer::ATimer() : BaseEntity(),
		_wait(1.0f),
		_random(0.0f),
		_nextTriggerTime(0.0)
	{
	}

	void ATimer::Initialize()
	{
		BaseEntity::Initialize();

		float wait = Util::RandomFloat(_wait - _random, _wait + _random);
		_nextTriggerTime = Time::Now() + wait;
		std::cout << "next trigger time: " << wait << std::endl;
	}

	void ATimer::Tick(double dt)
	{
		BaseEntity::Tick(dt);

		if (_nextTriggerTime < Time::Now())
		{
			float wait = Util::RandomFloat(_wait - _random, _wait + _random);
			_nextTriggerTime = Time::Now() + wait;
			std::cout << "next trigger time: " << wait << std::endl;

			TriggerTarget();
		}
	}

	bool ATimer::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("wait"))
		{
			return property.ValueAsFloat(_wait);
		}
		else if (property.IsKey("random"))
		{
			return property.ValueAsFloat(_random);
		}

		return BaseEntity::SetProperty(property);
	}
}
