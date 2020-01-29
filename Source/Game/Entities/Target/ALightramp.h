#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Target
{
    class ALightramp : public BaseEntity
    {
    public:

        ALightramp();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
