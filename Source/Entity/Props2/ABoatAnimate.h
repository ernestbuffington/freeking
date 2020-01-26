#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props2
{
    class ABoatAnimate : public IEntity
    {
    public:

        ABoatAnimate();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
