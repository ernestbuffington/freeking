#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Ai
{
    class ASyOilcan : public IEntity
    {
    public:

        ASyOilcan();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
