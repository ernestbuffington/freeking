#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Info
{
    class ANull : public IEntity
    {
    public:

        ANull();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
