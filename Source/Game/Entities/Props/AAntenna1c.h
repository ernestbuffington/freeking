#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class AAntenna1c : public IEntity
    {
    public:

        AAntenna1c();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
