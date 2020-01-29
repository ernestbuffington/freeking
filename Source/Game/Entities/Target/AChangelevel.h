#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Target
{
    class AChangelevel : public BaseEntity
    {
    public:

        AChangelevel();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
