#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Light
{
    class AMine1 : public BaseEntity
    {
    public:

        AMine1();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
