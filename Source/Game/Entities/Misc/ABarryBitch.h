#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Misc
{
    class ABarryBitch : public BaseEntity
    {
    public:

        ABarryBitch();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
