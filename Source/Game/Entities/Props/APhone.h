#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class APhone : public IEntity
    {
    public:

        APhone();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
