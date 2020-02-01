#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class ARatSpawnerNode : public BaseEntity
    {
    public:

        ARatSpawnerNode();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
