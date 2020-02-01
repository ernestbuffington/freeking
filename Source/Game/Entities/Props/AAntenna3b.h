#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AAntenna3b : public BaseEntity
    {
    public:

        AAntenna3b();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
