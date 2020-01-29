#include "ShaderLoader.h"
#include "ShaderProgram.h"

namespace Freeking
{
	bool ShaderLoader::CanLoadExtension(const std::string& extension) const
	{
		if (extension == ".shader") return true;

		return false;
	};

	ShaderLoader::AssetPtr ShaderLoader::Load(const std::string& name) const
	{
		return nullptr;
	}
}
