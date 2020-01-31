#pragma once

#include "IEntity.h"

namespace Freeking::Entity
{
    class AViewthing : public IEntity
    {
    public:

        AViewthing();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
