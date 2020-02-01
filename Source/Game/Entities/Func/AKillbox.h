#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Func
{
    class AKillbox : public BaseEntity
    {
    public:

        AKillbox();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
