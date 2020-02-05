#pragma once

#include "SceneEntity.h"

namespace Freeking::Entity
{
    class ALightflare : public SceneEntity
    {
    public:

        ALightflare();

        virtual void Spawn() override;
    };
}
