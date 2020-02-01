#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class ARadio : public BaseEntity
    {
    public:

        ARadio();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
