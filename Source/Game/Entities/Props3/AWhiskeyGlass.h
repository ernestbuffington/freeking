#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props3
{
    class AWhiskeyGlass : public BaseEntity
    {
    public:

        AWhiskeyGlass();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
