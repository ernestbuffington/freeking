#include "ASpeaker.h"
#include "LineRenderer.h"
#include "Audio/AudioDevice.h"
#include "Audio/AudioClip.h"
#include <filesystem>

namespace Freeking::Entity::Target
{
	ASpeaker::ASpeaker() : SceneEntity(),
		_spawnFlags(SpawnFlags::None),
		_noise(""),
		_attenuation(1),
		_volume(1.0f),
		_audioClip(nullptr)
	{
	}

	void ASpeaker::Initialize()
	{
		SceneEntity::Initialize();

		auto noisePath = std::filesystem::path("sound") / _noise;
		noisePath.replace_extension("wav");

		if (const auto& audioClip = AudioClip::Library.Get(noisePath.string()))
		{
			if (_audioClip = audioClip.get(); _audioClip)
			{
				if (_spawnFlags[SpawnFlags::LoopedOn])
				{
					AudioDevice::Current->Play(_audioClip, GetPosition(), true, false, true);
				}
			}
		}
	}

	void ASpeaker::Tick(double dt)
	{
		SceneEntity::Tick(dt);
	}

	void ASpeaker::OnTrigger()
	{
		if (_audioClip)
		{
			AudioDevice::Current->Play(_audioClip, GetPosition(), false, _attenuation == -1);
		}
	}

	bool ASpeaker::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("spawnflags"))
		{
			return property.ValueAsFlags(_spawnFlags);
		}
		else if (property.IsKey("noise"))
		{
			_noise = property.Value();

			return true;
		}
		else if (property.IsKey("attenuation"))
		{
			return property.ValueAsInt(_attenuation);
		}
		else if (property.IsKey("volume"))
		{
			return property.ValueAsFloat(_volume);
		}

		return SceneEntity::SetProperty(property);
	}
}
