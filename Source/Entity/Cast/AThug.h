#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Cast
{
    class AThug : public IEntity
    {
    public:

        AThug();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
