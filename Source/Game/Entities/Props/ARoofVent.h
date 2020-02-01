#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class ARoofVent : public BaseEntity
    {
    public:

        ARoofVent();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
