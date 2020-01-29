#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props2
{
    class ABarrelsPvD : public BaseEntity
    {
    public:

        ABarrelsPvD();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
