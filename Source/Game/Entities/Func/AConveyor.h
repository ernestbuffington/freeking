#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Func
{
    class AConveyor : public BaseEntity
    {
    public:

        AConveyor();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
