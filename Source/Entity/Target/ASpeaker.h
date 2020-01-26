#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Target
{
    class ASpeaker : public IEntity
    {
    public:

        ASpeaker();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
