#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Light
{
    class AFireEsm : public IEntity
    {
    public:

        AFireEsm();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
