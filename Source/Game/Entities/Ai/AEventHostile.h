#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Ai
{
    class AEventHostile : public BaseEntity
    {
    public:

        AEventHostile();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
