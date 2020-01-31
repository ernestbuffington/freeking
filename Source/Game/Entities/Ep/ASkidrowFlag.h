#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Ep
{
    class ASkidrowFlag : public IEntity
    {
    public:

        ASkidrowFlag();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
