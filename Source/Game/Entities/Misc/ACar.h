#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Misc
{
    class ACar : public BaseEntity
    {
    public:

        ACar();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
