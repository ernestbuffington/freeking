#pragma once

#include "AssetLibrary.h"

namespace Freeking
{
	class Texture2D;

	class TextureLoader : public AssetLoader<Texture2D>
	{
	public:

		virtual bool CanLoadExtension(const std::string& extension) const override;
		virtual AssetPtr Load(const std::string& name) const override;
	};
}
