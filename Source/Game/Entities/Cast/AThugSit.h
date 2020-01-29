#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Cast
{
    class AThugSit : public BaseEntity
    {
    public:

        AThugSit();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
