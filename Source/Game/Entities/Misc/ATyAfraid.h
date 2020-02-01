#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Misc
{
    class ATyAfraid : public BaseEntity
    {
    public:

        ATyAfraid();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
