#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AAircon : public BaseEntity
    {
    public:

        AAircon();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
