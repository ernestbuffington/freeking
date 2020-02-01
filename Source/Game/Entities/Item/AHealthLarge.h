#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Item
{
    class AHealthLarge : public BaseEntity
    {
    public:

        AHealthLarge();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
