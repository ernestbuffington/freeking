#include "WavLoader.h"
#include "MemoryStream.h"

namespace Freeking
{
	AudioClipLibrary AudioClip::Library;

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

	bool WavLoader::CanLoadExtension(const std::string& extension) const
	{
		if (extension == ".wav") return true;

		return false;
	};

	WavLoader::AssetPtr WavLoader::Load(const std::string& name) const
	{
		auto fileData = FileSystem::GetFileData(name);

		if (fileData.empty())
		{
			return nullptr;
		}

		MemoryStream stream(fileData);

		static const char* RiffTag = "RIFF";
		static const char* WavTag = "WAVE";
		static const char* FormatTag = "fmt ";

		char ident[4];

		stream.Read((uint8_t*)&ident[0], 4);
		if (strncmp(ident, RiffTag, 4) != 0)
		{
			return nullptr;
		}

		auto fileSize = stream.Read<uint32_t>();

		stream.Read((uint8_t*)&ident[0], 4);
		if (strncmp(ident, WavTag, 4) != 0)
		{
			return nullptr;
		}

		do
		{
			stream.Read((uint8_t*)&ident[0], 4);
		} while ((strncmp(ident, FormatTag, 4) != 0) && !stream.End());

		if (stream.End())
		{
			return nullptr;
		}

		stream.Seek(4, SeekMode::Current);

		RiffFormatChunk riffChunk;
		stream.Read((uint8_t*)&riffChunk, sizeof(RiffFormatChunk));

		if (riffChunk.wFormatTag != 1)
		{
			return nullptr;
		}

		if (riffChunk.nChannels != 1 && riffChunk.nChannels != 2)
		{
			return nullptr;
		}

		if (riffChunk.wBitsPerSample != 8 && riffChunk.wBitsPerSample != 16)
		{
			return nullptr;
		}

		uint32_t chunkId;
		uint32_t chunkSize;
		uint32_t dataSize = 0;
		std::vector<char> pcmData;

		for (uint32_t i = 12; i < fileSize;)
		{
			stream.Seek(i, SeekMode::Begin);
			stream.Read((uint8_t*)&chunkId, sizeof(chunkId));
			stream.Read((uint8_t*)&chunkSize, sizeof(chunkSize));

			if (chunkId == 'atad')
			{
				pcmData.clear();
				pcmData.resize(chunkSize, 0);
				stream.Read((uint8_t*)&pcmData[0], chunkSize);
				dataSize = chunkSize;

				break;
			}

			chunkSize += 8;
			chunkSize += 1;
			chunkSize &= 0xfffffffe;
			i += chunkSize;
		}

		auto bitsPerSample = riffChunk.wBitsPerSample;
		auto channelCount = riffChunk.nChannels;
		auto samplesPerSecond = riffChunk.nSamplesPerSec;

		return std::make_shared<AudioClip>(channelCount, bitsPerSample, samplesPerSecond, pcmData);
	}
}
