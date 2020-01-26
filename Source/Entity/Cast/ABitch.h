#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Cast
{
    class ABitch : public IEntity
    {
    public:

        ABitch();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
