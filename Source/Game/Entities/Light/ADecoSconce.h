#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Light
{
    class ADecoSconce : public BaseEntity
    {
    public:

        ADecoSconce();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
