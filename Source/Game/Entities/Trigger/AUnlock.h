#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Trigger
{
    class AUnlock : public BaseEntity
    {
    public:

        AUnlock();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
