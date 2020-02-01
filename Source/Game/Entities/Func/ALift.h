#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Func
{
    class ALift : public BaseEntity
    {
    public:

        ALift();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
