#pragma once

#include "Vector.h"
#include "Quaternion.h"
#include <vector>
#include <array>
#include <stdint.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/efx.h>

namespace Freeking
{
	class AudioClip;

	struct PlaySound
	{
		uint32_t bufferId;
		Vector3f position;
	};

	class AudioDevice
	{
	public:

		static AudioDevice* Current;

		AudioDevice();
		~AudioDevice();

		void Play();
		void Play(AudioClip* audioClip, const Vector3f& position);

		void SetListenerTransform(const Vector3f& position, const Quaternion& rotation);

		std::vector<PlaySound> Sounds;

	private:

		void InitializeOpenAl();
		void ShutdownOpenAL();

		ALCcontext* _alContext;
		ALCdevice* _alDevice;

		std::array<uint32_t, 255> _sourceIds;

		ALCint _numMonoSources;
		ALCint _numStereoSources;
	};
}
