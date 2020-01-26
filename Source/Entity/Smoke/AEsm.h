#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Smoke
{
    class AEsm : public IEntity
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
