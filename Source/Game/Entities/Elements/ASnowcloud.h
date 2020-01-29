#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Elements
{
    class ASnowcloud : public BaseEntity
    {
    public:

        ASnowcloud();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
