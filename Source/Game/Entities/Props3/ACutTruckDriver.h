#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props3
{
    class ACutTruckDriver : public BaseEntity
    {
    public:

        ACutTruckDriver();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
