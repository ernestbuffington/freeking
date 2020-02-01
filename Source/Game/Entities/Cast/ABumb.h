#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Cast
{
    class ABumb : public BaseEntity
    {
    public:

        ABumb();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
