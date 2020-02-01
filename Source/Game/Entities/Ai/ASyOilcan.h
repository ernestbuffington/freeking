#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Ai
{
    class ASyOilcan : public BaseEntity
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
