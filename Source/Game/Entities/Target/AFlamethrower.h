#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Target
{
    class AFlamethrower : public BaseEntity
    {
    public:

        AFlamethrower();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
