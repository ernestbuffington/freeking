#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Path
{
    class ACornerCast : public IEntity
    {
    public:

        ACornerCast();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
