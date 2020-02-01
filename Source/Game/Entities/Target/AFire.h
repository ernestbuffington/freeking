#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Target
{
    class AFire : public BaseEntity
    {
    public:

        AFire();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
