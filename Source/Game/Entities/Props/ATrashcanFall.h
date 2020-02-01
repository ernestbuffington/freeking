#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class ATrashcanFall : public BaseEntity
    {
    public:

        ATrashcanFall();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
