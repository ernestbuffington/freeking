#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class APhone : public BaseEntity
    {
    public:

        APhone();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
