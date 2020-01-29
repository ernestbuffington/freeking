#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Func
{
    class AWater : public BaseEntity
    {
    public:

        AWater();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
