#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Func
{
    class ASubdoorHandle1 : public BaseEntity
    {
    public:

        ASubdoorHandle1();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
