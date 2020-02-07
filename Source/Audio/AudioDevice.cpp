#include "AudioDevice.h"
#include "AudioClip.h"
#include <stdexcept>

namespace Freeking
{
	AudioDevice* AudioDevice::Current = nullptr;

	AudioDevice::AudioDevice()
	{
		Current = this;

		InitializeOpenAl();
	}

	AudioDevice::~AudioDevice()
	{
		ShutdownOpenAL();
	}

	void AudioDevice::Play(AudioClip* audioClip, const Vector3f& position)
	{
		auto sourceId = _sourceIds[254];
		alSourcei(sourceId, AL_BUFFER, audioClip->GetBufferId());
		alSourcei(sourceId, AL_LOOPING, AL_FALSE);
		alSource3f(sourceId, AL_POSITION, position.x, position.y, position.z);
		alSourcePlay(sourceId);
	}

	void AudioDevice::Play()
	{
		for (int i = 0; i < Sounds.size(); ++i)
		{
			const auto& sound = Sounds[i];
			auto sourceId = _sourceIds[i];
			alSourcei(sourceId, AL_BUFFER, sound.bufferId);
			alSource3f(sourceId, AL_POSITION, sound.position.x, sound.position.y, sound.position.z);
		}

		alSourcePlayv((int)Sounds.size(), _sourceIds.data());

		Sounds.clear();
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

		alGenSources((int)_sourceIds.size(), _sourceIds.data());

		for (const auto& sourceId : _sourceIds)
		{
			alSourcei(sourceId, AL_LOOPING, AL_TRUE);
			alSourcef(sourceId, AL_PITCH, 1);
			alSourcef(sourceId, AL_GAIN, 1);
			alSourcei(sourceId, AL_SOURCE_RELATIVE, AL_FALSE);
			alSourcef(sourceId, AL_REFERENCE_DISTANCE, 0.0f);
			alSourcef(sourceId, AL_MAX_DISTANCE, 400.0f);
		}

		alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
	}

	void AudioDevice::ShutdownOpenAL()
	{
		alDeleteSources((int)_sourceIds.size(), _sourceIds.data());

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
