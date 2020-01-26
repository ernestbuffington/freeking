#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Misc
{
    class ASkidrowRadio : public IEntity
    {
    public:

        ASkidrowRadio();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
