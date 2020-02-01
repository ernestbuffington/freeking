#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Path
{
    class ACornerCast : public BaseEntity
    {
    public:

        ACornerCast();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
