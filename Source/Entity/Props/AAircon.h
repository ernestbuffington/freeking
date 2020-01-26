#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class AAircon : public IEntity
    {
    public:

        AAircon();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
