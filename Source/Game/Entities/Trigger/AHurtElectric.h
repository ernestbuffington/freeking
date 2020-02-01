#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Trigger
{
    class AHurtElectric : public BaseEntity
    {
    public:

        AHurtElectric();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
