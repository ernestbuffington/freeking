#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Misc
{
    class APvAfraid : public IEntity
    {
    public:

        APvAfraid();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
