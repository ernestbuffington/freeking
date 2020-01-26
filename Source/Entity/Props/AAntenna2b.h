#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class AAntenna2b : public IEntity
    {
    public:

        AAntenna2b();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
