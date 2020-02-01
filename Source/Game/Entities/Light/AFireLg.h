#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Light
{
    class AFireLg : public BaseEntity
    {
    public:

        AFireLg();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
