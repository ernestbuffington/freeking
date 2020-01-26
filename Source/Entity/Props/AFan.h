#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class AFan : public IEntity
    {
    public:

        AFan();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
