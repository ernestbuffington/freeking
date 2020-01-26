#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Hmg
{
    class AModCooling : public IEntity
    {
    public:

        AModCooling();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
