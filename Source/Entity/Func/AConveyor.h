#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Func
{
    class AConveyor : public IEntity
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
