#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Item
{
    class AHealthLarge : public IEntity
    {
    public:

        AHealthLarge();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
