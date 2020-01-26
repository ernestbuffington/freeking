#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Ai
{
    class AMokerNotinoffice : public IEntity
    {
    public:

        AMokerNotinoffice();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
