#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Info
{
    class APlayerStart : public BaseEntity
    {
    public:

        APlayerStart();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
