#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Func
{
    class ASubdoorHandle2 : public BaseEntity
    {
    public:

        ASubdoorHandle2();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
