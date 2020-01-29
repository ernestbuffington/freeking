#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Smoke
{
    class AEsm : public BaseEntity
    {
    public:

        AEsm();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
