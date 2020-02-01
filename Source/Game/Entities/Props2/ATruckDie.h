#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props2
{
    class ATruckDie : public BaseEntity
    {
    public:

        ATruckDie();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
