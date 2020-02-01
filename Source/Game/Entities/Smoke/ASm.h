#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Smoke
{
    class ASm : public BaseEntity
    {
    public:

        ASm();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
