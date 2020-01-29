#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Cast
{
    class APunkWindow : public BaseEntity
    {
    public:

        APunkWindow();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
