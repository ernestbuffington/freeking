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
		alSourcePlay(_sourceId);
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

		alGenSources(1, &_sourceId);
	}

	void AudioDevice::ShutdownOpenAL()
	{
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

		alDeleteSources(1, &_sourceId);
	}
}
