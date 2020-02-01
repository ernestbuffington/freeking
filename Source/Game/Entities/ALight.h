#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity
{
    class ALight : public BaseEntity
    {
    public:

        ALight();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
