#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Misc
{
    class AGibLeg : public BaseEntity
    {
    public:

        AGibLeg();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
