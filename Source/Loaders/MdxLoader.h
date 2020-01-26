#pragma once

#include "AssetLibrary.h"

namespace Freeking
{
	class KeyframeMesh;

	class MDXLoader : public AssetLoader<KeyframeMesh>
	{
	public:

		virtual bool CanLoadExtension(const std::string& extension) const override;
		virtual AssetPtr Load(const std::string& name) const override;
	};
}
