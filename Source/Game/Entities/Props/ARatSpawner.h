#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class ARatSpawner : public IEntity
    {
    public:

        ARatSpawner();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
