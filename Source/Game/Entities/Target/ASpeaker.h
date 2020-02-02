#pragma once

#include "SceneEntity.h"

namespace Freeking::Entity::Target
{
    class ASpeaker : public SceneEntity
    {
    public:

        ASpeaker();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

    private:

        enum class SpawnFlags : uint32_t
        {
            None = 0,
            LoopedOn = 1,
            LoopOff = 2,
            Important = 4
        };

        std::string _noise;
        float _attenuation;
        float _volume;
        SpawnFlags _spawnFlags;
    };
}
