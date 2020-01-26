#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class AAntenna3b : public IEntity
    {
    public:

        AAntenna3b();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
