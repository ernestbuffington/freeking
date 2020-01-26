#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props2
{
    class ATruckDie : public IEntity
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
