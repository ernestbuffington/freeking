#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AAntenna2c : public BaseEntity
    {
    public:

        AAntenna2c();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
