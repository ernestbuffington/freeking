#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Info
{
    class APlayerDeathmatch : public BaseEntity
    {
    public:

        APlayerDeathmatch();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
