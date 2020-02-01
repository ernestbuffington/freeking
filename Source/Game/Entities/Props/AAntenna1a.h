#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class AAntenna1a : public BaseEntity
    {
    public:

        AAntenna1a();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
