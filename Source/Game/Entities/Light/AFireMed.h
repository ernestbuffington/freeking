#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Light
{
    class AFireMed : public BaseEntity
    {
    public:

        AFireMed();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
