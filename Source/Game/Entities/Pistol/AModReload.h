#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Pistol
{
    class AModReload : public IEntity
    {
    public:

        AModReload();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
