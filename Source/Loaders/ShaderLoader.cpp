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
		auto source = FileSystem::GetFileData(name);

		if (source.empty() || source.empty())
		{
			return nullptr;
		}

		return std::make_shared<ShaderProgram>(std::string(source.data(), source.size()));
	}
}
