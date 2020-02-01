#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Dm
{
    class ASafebag : public BaseEntity
    {
    public:

        ASafebag();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
