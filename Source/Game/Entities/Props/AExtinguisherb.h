#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class AExtinguisherb : public IEntity
    {
    public:

        AExtinguisherb();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}