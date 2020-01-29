#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class ATrashcorner : public BaseEntity
    {
    public:

        ATrashcorner();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
