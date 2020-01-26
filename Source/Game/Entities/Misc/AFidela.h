#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Misc
{
    class AFidela : public IEntity
    {
    public:

        AFidela();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
