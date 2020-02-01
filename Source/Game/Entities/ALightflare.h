#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity
{
    class ALightflare : public BaseEntity
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
