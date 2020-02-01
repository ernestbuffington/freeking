#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Hmg
{
    class AModCooling : public BaseEntity
    {
    public:

        AModCooling();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
