#include "ShaderLoader.h"
#include "Shader.h"

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

		if (source.empty())
		{
			return nullptr;
		}

		auto shader = std::make_shared<Shader>();
		shader->Compile(std::string((char*)source.data(), source.size()));

		return shader;
	}
}
