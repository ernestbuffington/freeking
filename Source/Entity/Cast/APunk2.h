#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Cast
{
    class APunk2 : public IEntity
    {
    public:

        APunk2();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
