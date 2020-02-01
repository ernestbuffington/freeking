#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AChair : public BaseEntity
    {
    public:

        AChair();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
