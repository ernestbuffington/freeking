#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props3
{
    class ACutCAnimate : public BaseEntity
    {
    public:

        ACutCAnimate();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
