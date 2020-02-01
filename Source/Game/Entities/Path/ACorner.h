#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Path
{
    class ACorner : public BaseEntity
    {
    public:

        ACorner();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
