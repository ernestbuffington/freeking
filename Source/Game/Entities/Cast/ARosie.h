#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Cast
{
    class ARosie : public BaseEntity
    {
    public:

        ARosie();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
