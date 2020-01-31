#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class ATrashpaper : public IEntity
    {
    public:

        ATrashpaper();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
