#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Trigger
{
    class AHurt : public IEntity
    {
    public:

        AHurt();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
