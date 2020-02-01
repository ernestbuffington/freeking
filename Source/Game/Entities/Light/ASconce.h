#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Light
{
    class ASconce : public BaseEntity
    {
    public:

        ASconce();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
