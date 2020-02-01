#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Trigger
{
    class ACounter : public BaseEntity
    {
    public:

        ACounter();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
