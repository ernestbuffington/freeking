#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Sfx
{
    class ABeacon : public IEntity
    {
    public:

        ABeacon();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
