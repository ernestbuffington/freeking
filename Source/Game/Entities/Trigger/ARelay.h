#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Trigger
{
    class ARelay : public BaseEntity
    {
    public:

        ARelay();

		virtual void Tick(double dt) override;

	protected:

        virtual void Trigger() override;

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

        float _delay;
        double _timeToTrigger;
        bool _triggered;
    };
}
