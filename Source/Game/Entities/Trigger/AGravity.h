#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Trigger
{
    class AGravity : public BaseEntity
    {
    public:

        AGravity();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
