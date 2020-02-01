#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Pawn
{
    class AOMatic : public BaseEntity
    {
    public:

        AOMatic();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
