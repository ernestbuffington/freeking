#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Misc
{
    class AGibLeg : public IEntity
    {
    public:

        AGibLeg();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
