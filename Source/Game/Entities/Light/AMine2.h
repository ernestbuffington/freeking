#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Light
{
    class AMine2 : public IEntity
    {
    public:

        AMine2();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
