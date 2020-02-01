#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Func
{
    class APlat : public BaseEntity
    {
    public:

        APlat();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
