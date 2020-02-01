#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class ABlimp : public BaseEntity
    {
    public:

        ABlimp();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
