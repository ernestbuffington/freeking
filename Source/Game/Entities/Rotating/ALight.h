#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Rotating
{
    class ALight : public IEntity
    {
    public:

        ALight();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
