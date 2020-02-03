#include "AudioDevice.h"
#include "AudioClip.h"
#include <stdexcept>

namespace Freeking
{
	AudioDevice::AudioDevice()
	{
		InitializeOpenAl();
	}

	AudioDevice::~AudioDevice()
	{
		ShutdownOpenAL();
	}

	void AudioDevice::PlayClip(AudioClip* clip)
	{
		if (!clip)
		{
			return;
		}

		alSourcei(_sourceId, AL_BUFFER, clip->GetBufferId());
		alSourcei(_sourceId, AL_LOOPING, AL_TRUE);
		alSourcef(_sourceId, AL_PITCH, 1);
		alSourcef(_sourceId, AL_GAIN, 1);
		alSource3f(_sourceId, AL_POSITION, 0, 0, 0);

		alSourcei(_sourceId, AL_SOURCE_RELATIVE, AL_FALSE);
		alSourcef(_sourceId, AL_REFERENCE_DISTANCE, 0.0f);
		alSourcef(_sourceId, AL_MAX_DISTANCE, 800.0f);
		alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);

		alSourcePlay(_sourceId);
	}

	void AudioDevice::SetListenerTransform(const Vector3f& position, const Quaternion& rotation)
	{
		alListener3f(AL_POSITION, position.x, position.y, position.z);

		Vector3f forward = rotation * Vector3f::Forward;
		Vector3f up = rotation * Vector3f::Up;
		float orientation[6] = { forward[0], forward[1], forward[2], up[0], up[1], up[2] };

		alListenerfv(AL_ORIENTATION, orientation);
	}

	void AudioDevice::InitializeOpenAl()
	{	
		if (_alDevice = alcOpenDevice(nullptr); !_alDevice)
		{
			throw std::runtime_error("Failed to open OpenAL device.");
		}

		if (_alContext = alcCreateContext(_alDevice, nullptr); !_alContext)
		{
			throw std::runtime_error("Failed to create OpenAL context.");
		}

		alcMakeContextCurrent(_alContext);

		alcGetIntegerv(_alDevice, ALC_MONO_SOURCES, 1, &_numMonoSources);
		alcGetIntegerv(_alDevice, ALC_STEREO_SOURCES, 1, &_numStereoSources);

		alGenSources(1, &_sourceId);
	}

	void AudioDevice::ShutdownOpenAL()
	{
		if (_sourceId)
		{
			alDeleteSources(1, &_sourceId);

			_sourceId = 0;
		}

		if (_alContext)
		{
			alcMakeContextCurrent(nullptr);
			alcDestroyContext(_alContext);

			_alContext = nullptr;
		}

		if (_alDevice)
		{
			alcCloseDevice(_alDevice);

			_alDevice = nullptr;
		}
	}
}
