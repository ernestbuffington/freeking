#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AColaMachine : public BaseEntity
    {
    public:

        AColaMachine();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
