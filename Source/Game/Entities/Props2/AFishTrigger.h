#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props2
{
    class AFishTrigger : public IEntity
    {
    public:

        AFishTrigger();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
