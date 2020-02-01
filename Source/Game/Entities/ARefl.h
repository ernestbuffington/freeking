#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity
{
    class ARefl : public BaseEntity
    {
    public:

        ARefl();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
