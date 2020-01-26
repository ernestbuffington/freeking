#pragma once

#include "IEntity.h"

namespace Freeking::Entity
{
    class ALightflare : public IEntity
    {
    public:

        ALightflare();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
