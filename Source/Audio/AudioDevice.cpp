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

	void AudioDevice::FlushQueue()
	{
		if (_audioQueue.empty())
		{
			return;
		}

		std::vector<uint32_t> sourceIds;

		for (int i = 0, queueIndex = 0; i < _sourceIds.size(); ++i)
		{
			ALenum state;
			auto sourceId = _sourceIds[i];
			alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

			if (state == AL_PLAYING)
			{
				continue;
			}

			const auto& queuedAudio = _audioQueue.at(queueIndex);
			sourceIds.push_back(sourceId);

			alSourceStop(sourceId);
			alSourcei(sourceId, AL_BUFFER, queuedAudio.audioClip->GetBufferId());
			alSourcei(sourceId, AL_LOOPING, queuedAudio.loop ? AL_TRUE : AL_FALSE);
			alSourcei(sourceId, AL_SOURCE_RELATIVE, queuedAudio.relative ? AL_TRUE : AL_FALSE);

			if (queuedAudio.relative)
			{
				alSource3f(sourceId, AL_POSITION, 0, 0, 0);
			}
			else
			{
				alSource3f(sourceId, AL_POSITION, queuedAudio.position.x, queuedAudio.position.y, queuedAudio.position.z);
			}

			queueIndex++;

			if (queueIndex < _audioQueue.size())
			{
				continue;
			}
			else
			{
				break;
			}
		}

		alSourcePlayv(sourceIds.size(), sourceIds.data());

		_audioQueue.clear();
	}

	void AudioDevice::Play(AudioClip* audioClip, const Vector3f& position, bool loop, bool relative, bool queued)
	{
		if (audioClip == nullptr)
		{
			return;
		}

		if (queued)
		{
			_audioQueue.push_back(
				{
					audioClip,
					position,
					loop,
					relative
				});

			return;
		}

		for (int i = 0; i < _sourceIds.size(); ++i)
		{
			ALenum state;
			auto sourceId = _sourceIds[i];
			alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

			if (state == AL_PLAYING)
			{
				continue;
			}

			alSourceStop(sourceId);
			alSourcei(sourceId, AL_BUFFER, audioClip->GetBufferId());
			alSourcei(sourceId, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
			alSourcei(sourceId, AL_SOURCE_RELATIVE, relative ? AL_TRUE : AL_FALSE);

			if (relative)
			{
				alSource3f(sourceId, AL_POSITION, 0, 0, 0);
			}
			else
			{
				alSource3f(sourceId, AL_POSITION, position.x, position.y, position.z);
			}

			alSourcePlay(sourceId);

			break;
		}
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
			alSourcei(sourceId, AL_LOOPING, AL_FALSE);
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
