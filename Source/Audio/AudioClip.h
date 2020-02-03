#pragma once

#include "AssetLibrary.h"
#include <vector>

namespace Freeking
{
	class AudioClip;

	class AudioClipLibrary : public AssetLibrary<AudioClip>
	{
	protected:

		virtual void UpdateLoaders() override;
	};

	class AudioClip
	{
	public:

		static AudioClipLibrary Library;

		AudioClip(uint32_t numChannels, uint32_t bitsPerSample, uint32_t sampleRate, const std::vector<char>& pcmData);
		~AudioClip();

		uint32_t GetBufferId() const { return _bufferId; }

	private:

		uint32_t _bufferId;
	};
}
