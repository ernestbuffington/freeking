#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Trigger
{
    class AMonsterjump : public BaseEntity
    {
    public:

        AMonsterjump();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
