#pragma once

#include "BrushModelEntity.h"
#include "EnumFlags.h"

namespace Freeking::Entity::Func
{
    class AWall : public BrushModelEntity
    {
    public:

        AWall();

        virtual void Initialize() override;

    protected:

        virtual void OnTrigger() override;

        virtual bool SetProperty(const EntityProperty& property) override;

        virtual bool HasSurf2Alpha() const override { return _spawnFlags[SpawnFlags::Surf2Alpha]; }

    private:

        enum class SpawnFlags : uint32_t
        {
            None = 0,
            TriggerSpawn = 1,
            Toggle = 2,
            StartOn = 4,
            Animated = 8,
            AnimatedFast = 16,
            Surf2Alpha = 32,
            NotEasy = 256,
            NotMedium = 512,
            NotHard = 1024,
            NotDeathmatch = 2048,
            NotCoop = 4096,
        };

        EnumFlags<SpawnFlags> _spawnFlags;
    };
}
