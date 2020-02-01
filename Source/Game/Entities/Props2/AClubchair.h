#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props2
{
    class AClubchair : public BaseEntity
    {
    public:

        AClubchair();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
