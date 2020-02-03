#include "AudioClip.h"
#include "WavLoader.h"

#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/efx.h>

namespace Freeking
{
	void AudioClipLibrary::UpdateLoaders()
	{
		AddLoader<WavLoader>();
	}

	AudioClip::AudioClip(uint32_t numChannels, uint32_t bitsPerSample, uint32_t sampleRate, const std::vector<char>& pcmData) :
		_bufferId(0)
	{
		ALenum format = AL_INVALID_ENUM;
		if (numChannels == 1)
		{
			if (bitsPerSample == 8) format = AL_FORMAT_MONO8;
			else if (bitsPerSample == 16) format = AL_FORMAT_MONO16;
		}
		else if (numChannels == 2)
		{
			if (bitsPerSample == 8) format = AL_FORMAT_STEREO8;
			else if (bitsPerSample == 16) format = AL_FORMAT_STEREO16;
		}

		alGenBuffers(1, &_bufferId);
		alBufferData(_bufferId, format, pcmData.data(), (ALsizei)pcmData.size(), sampleRate);
	}

	AudioClip::~AudioClip()
	{
		if (_bufferId)
		{
			alDeleteBuffers(1, &_bufferId);
		}
	}
}
