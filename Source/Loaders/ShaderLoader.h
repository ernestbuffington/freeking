#pragma once

#include "AssetLibrary.h"

namespace Freeking
{
	class ShaderProgram;

	class ShaderLoader : public AssetLoader<ShaderProgram>
	{
	public:

		virtual bool CanLoadExtension(const std::string& extension) const override;
		virtual AssetPtr Load(const std::string& name) const override;
	};
}
