#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Smoke
{
    class ALg : public BaseEntity
    {
    public:

        ALg();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
