#pragma once

#include "AssetLibrary.h"

namespace Freeking
{
	class Font;

	class FontLoader : public AssetLoader<Font>
	{
	public:

		virtual bool CanLoadExtension(const std::string& extension) const override;
		virtual AssetPtr Load(const std::string& name) const override;
	};
}
