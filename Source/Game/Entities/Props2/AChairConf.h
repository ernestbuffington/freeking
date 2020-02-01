#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props2
{
    class AChairConf : public BaseEntity
    {
    public:

        AChairConf();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
