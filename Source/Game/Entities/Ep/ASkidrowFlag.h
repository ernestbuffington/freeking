#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Ep
{
    class ASkidrowFlag : public BaseEntity
    {
    public:

        ASkidrowFlag();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
