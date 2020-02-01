#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AExtinguisherb : public BaseEntity
    {
    public:

        AExtinguisherb();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
