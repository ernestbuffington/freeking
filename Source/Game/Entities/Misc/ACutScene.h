#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Misc
{
    class ACutScene : public IEntity
    {
    public:

        ACutScene();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
