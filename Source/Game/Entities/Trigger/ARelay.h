#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Trigger
{
    class ARelay : public IEntity
    {
    public:

        ARelay();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
