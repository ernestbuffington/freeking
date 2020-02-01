#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class ARat : public BaseEntity
    {
    public:

        ARat();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
