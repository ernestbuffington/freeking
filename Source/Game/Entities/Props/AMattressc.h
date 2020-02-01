#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AMattressc : public BaseEntity
    {
    public:

        AMattressc();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
