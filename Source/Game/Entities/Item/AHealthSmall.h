#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Item
{
    class AHealthSmall : public BaseEntity
    {
    public:

        AHealthSmall();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
