#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Target
{
    class AExplosion : public BaseEntity
    {
    public:

        AExplosion();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
