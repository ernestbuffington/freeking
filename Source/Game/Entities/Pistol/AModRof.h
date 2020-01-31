#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Pistol
{
    class AModRof : public IEntity
    {
    public:

        AModRof();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
