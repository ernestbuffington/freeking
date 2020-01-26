#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props2
{
    class AVasea : public IEntity
    {
    public:

        AVasea();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
