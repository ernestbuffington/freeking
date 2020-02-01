#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props2
{
    class AVaseb : public BaseEntity
    {
    public:

        AVaseb();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
