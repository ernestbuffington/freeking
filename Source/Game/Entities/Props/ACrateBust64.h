#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Props
{
    class ACrateBust64 : public IEntity
    {
    public:

        ACrateBust64();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
