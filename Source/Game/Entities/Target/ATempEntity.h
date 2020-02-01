#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Target
{
    class ATempEntity : public BaseEntity
    {
    public:

        ATempEntity();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
