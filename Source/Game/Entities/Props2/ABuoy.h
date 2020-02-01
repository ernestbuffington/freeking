#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props2
{
    class ABuoy : public BaseEntity
    {
    public:

        ABuoy();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
