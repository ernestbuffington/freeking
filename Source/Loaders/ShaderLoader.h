#pragma once

#include "AssetLibrary.h"

namespace Freeking
{
	class Shader;

	class ShaderLoader : public AssetLoader<Shader>
	{
	public:

		virtual bool CanLoadExtension(const std::string& extension) const override;
		virtual AssetPtr Load(const std::string& name) const override;
	};
}
