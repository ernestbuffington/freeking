#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Trigger
{
    class AAlways : public BaseEntity
    {
    public:

        AAlways();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
