#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Ai
{
    class ASafespot : public IEntity
    {
    public:

        ASafespot();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
