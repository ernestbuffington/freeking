#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Light
{
    class ADecoSconce : public IEntity
    {
    public:

        ADecoSconce();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
