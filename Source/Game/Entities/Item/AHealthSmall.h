#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Item
{
    class AHealthSmall : public IEntity
    {
    public:

        AHealthSmall();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}