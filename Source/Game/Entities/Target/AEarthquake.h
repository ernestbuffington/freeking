#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Target
{
    class AEarthquake : public BaseEntity
    {
    public:

        AEarthquake();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
