#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Ai
{
    class ASyDykesBoundry : public BaseEntity
    {
    public:

        ASyDykesBoundry();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
