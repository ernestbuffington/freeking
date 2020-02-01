#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Smoke
{
    class AMed : public BaseEntity
    {
    public:

        AMed();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
