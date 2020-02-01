#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Pistol
{
    class AModRof : public BaseEntity
    {
    public:

        AModRof();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
