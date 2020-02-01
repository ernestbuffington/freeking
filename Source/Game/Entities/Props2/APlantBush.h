#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props2
{
    class APlantBush : public BaseEntity
    {
    public:

        APlantBush();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
