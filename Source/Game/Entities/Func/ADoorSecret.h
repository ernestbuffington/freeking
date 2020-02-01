#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Func
{
    class ADoorSecret : public BaseEntity
    {
    public:

        ADoorSecret();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
