#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Func
{
    class AObjectRepair : public BaseEntity
    {
    public:

        AObjectRepair();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
