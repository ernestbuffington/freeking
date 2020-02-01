#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Rc
{
    class AInitiationBrush : public BaseEntity
    {
    public:

        AInitiationBrush();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
