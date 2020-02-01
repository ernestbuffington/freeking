#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AAmmocrateBust : public BaseEntity
    {
    public:

        AAmmocrateBust();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
