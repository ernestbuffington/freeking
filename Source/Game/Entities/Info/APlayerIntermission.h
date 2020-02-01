#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Info
{
    class APlayerIntermission : public BaseEntity
    {
    public:

        APlayerIntermission();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
