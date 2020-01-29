#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props3
{
    class ADecoFixture : public BaseEntity
    {
    public:

        ADecoFixture();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
