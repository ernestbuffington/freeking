#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Func
{
    class AObject : public BaseEntity
    {
    public:

        AObject();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
