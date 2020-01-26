#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Misc
{
    class ACorkyFidelMdxTga : public IEntity
    {
    public:

        ACorkyFidelMdxTga();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
