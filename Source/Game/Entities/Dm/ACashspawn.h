#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Dm
{
    class ACashspawn : public IEntity
    {
    public:

        ACashspawn();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
