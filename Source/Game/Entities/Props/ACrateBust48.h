#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class ACrateBust48 : public BaseEntity
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
