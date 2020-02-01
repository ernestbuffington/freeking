#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props2
{
    class ABoat : public BaseEntity
    {
    public:

        ABoat();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
