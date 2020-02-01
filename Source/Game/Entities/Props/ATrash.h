#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class ATrash : public BaseEntity
    {
    public:

        ATrash();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
