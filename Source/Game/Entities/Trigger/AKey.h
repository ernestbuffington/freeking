#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Trigger
{
    class AKey : public BaseEntity
    {
    public:

        AKey();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
