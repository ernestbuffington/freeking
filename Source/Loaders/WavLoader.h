#pragma once

#include "AssetLibrary.h"

namespace Freeking
{
	class WavLoader;
	class AudioClipLibrary;

	class AudioClip
	{
	public:

		static AudioClipLibrary Library;
	};

	class AudioClipLibrary : public AssetLibrary<AudioClip>
	{
	protected:

		virtual void UpdateLoaders() override
		{
			AddLoader<WavLoader>();
		}
	};

	struct RiffFormatChunk
	{
		uint16_t wFormatTag;
		uint16_t nChannels;
		uint32_t nSamplesPerSec;
		uint32_t nAvgBytesPerSec;
		uint16_t nBlockAlign;
		uint16_t wBitsPerSample;
		uint16_t cbSize;
	};

	class WavLoader : public AssetLoader<AudioClip>
	{
	public:

		virtual bool CanLoadExtension(const std::string& extension) const override;
		virtual AssetPtr Load(const std::string& name) const override;
	};
}
