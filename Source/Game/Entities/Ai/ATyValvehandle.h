#pragma once

#include "BaseEntity.h"

namespace Freeking::Entity::Ai
{
    class ATyValvehandle : public BaseEntity
    {
    public:

        ATyValvehandle();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

    private:

    };
}
