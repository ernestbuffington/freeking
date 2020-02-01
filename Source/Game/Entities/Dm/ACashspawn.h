#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Dm
{
    class ACashspawn : public BaseEntity
    {
    public:

        ACashspawn();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
