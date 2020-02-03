#include "ASpeaker.h"
#include "LineRenderer.h"

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
	}

	void ASpeaker::Tick(double dt)
	{
		SceneEntity::Tick(dt);
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
				if (attenuation == 0) _attenuation = 1.0f;
				else if (attenuation == -1) _attenuation = 0.0f;
				else _attenuation = static_cast<float>(attenuation);

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
