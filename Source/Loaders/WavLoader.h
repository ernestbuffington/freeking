#pragma once

#include "Audio/AudioClip.h"

namespace Freeking
{
	class WavLoader : public AssetLoader<AudioClip>
	{
	public:

		virtual bool CanLoadExtension(const std::string& extension) const override;
		virtual AssetPtr Load(const std::string& name) const override;
	};
}
