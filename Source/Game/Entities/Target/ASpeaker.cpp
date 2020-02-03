#include "ASpeaker.h"
#include "LineRenderer.h"
#include "Audio/AudioDevice.h"
#include "Audio/AudioClip.h"

namespace Freeking::Entity::Target
{
	ASpeaker::ASpeaker() : SceneEntity(),
		_spawnFlags(SpawnFlags::None),
		_noise(""),
		_attenuation(1),
		_volume(1.0f)
	{
	}

	void ASpeaker::Initialize()
	{
		SceneEntity::Initialize();

		if (_spawnFlags[SpawnFlags::LoopedOn])
		{
			const auto& sound = AudioClip::Library.Get("sound/" + _noise + ".wav");
			if (sound)
			{
				AudioDevice::Current->Sounds.push_back({ sound->GetBufferId(), GetPosition() });
			}
		}
	}

	void ASpeaker::Tick(double dt)
	{
		SceneEntity::Tick(dt);

		if (_noise == "world/cypress")
		{
			LineRenderer::Debug->DrawSphere(GetPosition(), 400, 8, 8, Vector4f(0, 1, 1, 1));
		}
	}

	bool ASpeaker::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("spawnflags"))
		{
			return property.ValueAsFlags(_spawnFlags);
		}
		else if(property.IsKey("noise"))
		{
			_noise = property.Value();

			return true;
		}
		else if (property.IsKey("attenuation"))
		{
			int attenuation;

			if (property.ValueAsInt(attenuation))
			{
				if (attenuation == 0) _attenuation = 1;
				else if (attenuation == -1) _attenuation = 0;
				else _attenuation = attenuation;

				return true;
			}

			return false;
		}
		else if (property.IsKey("volume"))
		{
			return property.ValueAsFloat(_volume);
		}

		return SceneEntity::SetProperty(property);
	}
}
