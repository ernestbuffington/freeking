#pragma once

#include "Vector.h"
#include "Quaternion.h"
#include <stdint.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/efx.h>

namespace Freeking
{
	class AudioClip;

	class AudioDevice
	{
	public:

		AudioDevice();
		~AudioDevice();

		void PlayClip(AudioClip* clip);

		void SetListenerTransform(const Vector3f& position, const Quaternion& rotation);

	private:

		void InitializeOpenAl();
		void ShutdownOpenAL();

		ALCcontext* _alContext;
		ALCdevice* _alDevice;

		uint32_t _sourceId;

		ALCint _numMonoSources;
		ALCint _numStereoSources;
	};
}
