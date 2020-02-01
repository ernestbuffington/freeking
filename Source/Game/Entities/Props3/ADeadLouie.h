#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props3
{
    class ADeadLouie : public BaseEntity
    {
    public:

        ADeadLouie();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
