#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Info
{
    class ANotnull : public BaseEntity
    {
    public:

        ANotnull();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
