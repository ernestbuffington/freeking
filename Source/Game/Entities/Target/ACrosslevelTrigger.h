#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Target
{
    class ACrosslevelTrigger : public BaseEntity
    {
    public:

        ACrosslevelTrigger();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
