#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Elements
{
    class ARaincloud : public IEntity
    {
    public:

        ARaincloud();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
