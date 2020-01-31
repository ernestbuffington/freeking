#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class ACrateBust48 : public IEntity
    {
    public:

        ACrateBust48();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
