#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class AChair : public BaseEntity
    {
    public:

        AChair();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
