#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Ai
{
    class ATriggerCharacter : public BaseEntity
    {
    public:

        ATriggerCharacter();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

    };
}
