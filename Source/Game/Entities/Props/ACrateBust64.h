#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Props
{
    class ACrateBust64 : public BaseEntity
    {
    public:

        ACrateBust64();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
