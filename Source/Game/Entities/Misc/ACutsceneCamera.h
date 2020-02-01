#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Misc
{
    class ACutsceneCamera : public BaseEntity
    {
    public:

        ACutsceneCamera();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
