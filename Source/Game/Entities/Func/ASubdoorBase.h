#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Func
{
    class ASubdoorBase : public BaseEntity
    {
    public:

        ASubdoorBase();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
