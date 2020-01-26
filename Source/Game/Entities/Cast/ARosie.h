#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Cast
{
    class ARosie : public IEntity
    {
    public:

        ARosie();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
