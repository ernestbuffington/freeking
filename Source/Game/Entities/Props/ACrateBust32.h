#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class ACrateBust32 : public BaseEntity
    {
    public:

        ACrateBust32();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
