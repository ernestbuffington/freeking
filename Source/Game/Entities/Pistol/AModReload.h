#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Pistol
{
    class AModReload : public BaseEntity
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
