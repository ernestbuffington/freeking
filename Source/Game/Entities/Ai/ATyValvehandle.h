#pragma once

#include "IEntity.h"

namespace Freeking::Entity::Ai
{
    class ATyValvehandle : public IEntity
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
