#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class AAntenna2a : public IEntity
    {
    public:

        AAntenna2a();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
