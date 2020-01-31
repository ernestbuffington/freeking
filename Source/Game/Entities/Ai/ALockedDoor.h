#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Ai
{
    class ALockedDoor : public IEntity
    {
    public:

        ALockedDoor();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
