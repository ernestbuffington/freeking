#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Func
{
    class ATimer : public BaseEntity
    {
    public:

        ATimer();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
