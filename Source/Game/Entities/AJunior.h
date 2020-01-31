#pragma once

#include "IEntity.h"

namespace Freeking::Entity
{
    class AJunior : public IEntity
    {
    public:

        AJunior();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
