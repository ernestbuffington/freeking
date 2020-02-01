#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AAntenna2a : public BaseEntity
    {
    public:

        AAntenna2a();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
