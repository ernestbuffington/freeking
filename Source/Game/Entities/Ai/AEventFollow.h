#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Ai
{
    class AEventFollow : public BaseEntity
    {
    public:

        AEventFollow();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
