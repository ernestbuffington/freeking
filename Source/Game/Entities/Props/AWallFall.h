#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AWallFall : public BaseEntity
    {
    public:

        AWallFall();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
