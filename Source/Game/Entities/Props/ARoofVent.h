#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class ARoofVent : public BaseEntity
    {
    public:

        ARoofVent();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
