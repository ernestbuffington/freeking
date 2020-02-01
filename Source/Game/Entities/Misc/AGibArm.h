#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Misc
{
    class AGibArm : public BaseEntity
    {
    public:

        AGibArm();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
