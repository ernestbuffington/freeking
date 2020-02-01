#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props2
{
    class ACarTopup : public BaseEntity
    {
    public:

        ACarTopup();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
