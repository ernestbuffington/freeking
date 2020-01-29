#pragma once

#include "AssetLibrary.h"

namespace Freeking
{
	class DynamicModel;

	class MDXLoader : public AssetLoader<DynamicModel>
	{
	public:

		virtual bool CanLoadExtension(const std::string& extension) const override;
		virtual AssetPtr Load(const std::string& name) const override;
	};
}
