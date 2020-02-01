#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Cast
{
    class ABuma : public BaseEntity
    {
    public:

        ABuma();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
