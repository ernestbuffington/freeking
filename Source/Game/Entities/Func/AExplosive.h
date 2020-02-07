#pragma once

#include "BrushModelEntity.h"
#include "EnumFlags.h"

namespace Freeking::Entity::Func
{
    class AExplosive : public BrushModelEntity
    {
    public:

        AExplosive();

    protected:

        virtual void OnTrigger() override;

        virtual bool SetProperty(const EntityProperty& property) override;

        virtual bool HasSurf2Alpha() const override { return _spawnFlags[SpawnFlags::Surf2Alpha]; }

    private:

        enum class SpawnFlags : uint32_t
        {
            None = 0,
            TriggerSpawn = 1,
            Animated = 2,
            AnimatedFast = 4,
            Surf2Alpha = 8,
            AutoSound = 16,
            CriticalOnly = 32,
            NotEasy = 256,
            NotMedium = 512,
            NotHard = 1024,
            NotDeathMatch = 2048,
            NotCoop = 4096,
            BitFlags_Max
        };

        EnumFlags<SpawnFlags> _spawnFlags;
    };
}
