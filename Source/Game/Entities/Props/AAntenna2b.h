#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AAntenna2b : public BaseEntity
    {
    public:

        AAntenna2b();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
