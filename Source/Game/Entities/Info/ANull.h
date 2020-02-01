#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Info
{
    class ANull : public BaseEntity
    {
    public:

        ANull();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
