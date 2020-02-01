#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Ai
{
    class ASyBlefty : public BaseEntity
    {
    public:

        ASyBlefty();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
