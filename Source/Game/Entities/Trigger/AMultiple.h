#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Trigger
{
    class AMultiple : public BaseEntity
    {
    public:

        AMultiple();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
