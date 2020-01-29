#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Rc
{
    class AInitiationObserver : public BaseEntity
    {
    public:

        AInitiationObserver();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
