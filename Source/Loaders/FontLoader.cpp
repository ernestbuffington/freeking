#include "FontLoader.h"
#include "Font.h"
#include "Texture2D.h"
#include "json.hpp"

namespace Freeking
{
	bool FontLoader::CanLoadExtension(const std::string& extension) const
	{
		if (extension == ".json") return true;

		return false;
	};

	FontLoader::AssetPtr FontLoader::Load(const std::string& name) const
	{
		auto buffer = FileSystem::GetFileData(name);
		if (buffer.empty())
		{
			return nullptr;
		}

		auto fontString = std::string(buffer.data(), buffer.size());
		auto fontJson = json::JSON::JSON::Load(fontString);

		std::vector<std::shared_ptr<Texture2D>> pageTextures;
		std::unordered_map<int32_t, Font::Character> characters;

		auto pages = fontJson["pages"];
		for (int i = 0; i < pages.size(); ++i)
		{
			std::filesystem::path fontPath(name);
			fontPath = fontPath.remove_filename();
			pageTextures.push_back(Texture2D::Library.Get(fontPath.append(pages[i].ToString()).string()));
		}

		auto chars = fontJson["chars"];
		for (int i = 0; i < chars.size(); ++i)
		{
			auto& c = chars[i];
			characters.emplace(
				c["id"].ToInt(),
				Font::Character
				{
					(uint32_t)c["id"].ToInt(),
					(float)c["x"].ToNumber(),
					(float)c["y"].ToNumber(),
					(float)c["width"].ToNumber(),
					(float)c["height"].ToNumber(),
					(float)c["xoffset"].ToNumber(),
					(float)c["yoffset"].ToNumber(),
					(float)c["xadvance"].ToNumber(),
					(uint32_t)c["page"].ToInt(),
				});
		}

		float lineHeight = (float)fontJson["common"]["lineHeight"].ToNumber();

		return std::make_shared<Font>(lineHeight, pageTextures, characters);
	}
}
