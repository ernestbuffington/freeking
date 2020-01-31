#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Func
{
    class ASubdoorHandle2 : public IEntity
    {
    public:

        ASubdoorHandle2();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
