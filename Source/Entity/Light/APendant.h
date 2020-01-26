#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Light
{
    class APendant : public IEntity
    {
    public:

        APendant();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
