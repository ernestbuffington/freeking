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
		if (fontString.empty())
		{
			return nullptr;
		}

		auto fontJson = json::JSON::JSON::Load(fontString);
		if (!fontJson.hasKey("pages") ||
			!fontJson.hasKey("chars") ||
			!fontJson.hasKey("common"))
		{
			return nullptr;
		}

		std::vector<std::shared_ptr<Texture2D>> pageTextures;
		std::unordered_map<int32_t, Font::Character> characters;

		const auto& pages = fontJson.at("pages");
		for (int i = 0; i < pages.size(); ++i)
		{
			std::filesystem::path fontPath(name);
			if (auto texture = Texture2D::Library.Get(fontPath.remove_filename().append(pages.at(i).ToString()).string()))
			{
				pageTextures.push_back(texture);
			}
			else
			{
				return nullptr;
			}
		}

		const auto& charsJson = fontJson.at("chars");
		for (int i = 0; i < charsJson.size(); ++i)
		{
			const auto& c = charsJson.at(i);

			if (!c.hasKey("id") ||
				!c.hasKey("x") || !c.hasKey("y") ||
				!c.hasKey("width") || !c.hasKey("height") ||
				!c.hasKey("xoffset") || !c.hasKey("yoffset") ||
				!c.hasKey("xadvance") ||
				!c.hasKey("page"))
			{
				continue;
			}

			characters.emplace(
				c.at("id").ToInt(),
				Font::Character
				{
					(uint32_t)c.at("id").ToInt(),
					(float)c.at("x").ToNumber(),
					(float)c.at("y").ToNumber(),
					(float)c.at("width").ToNumber(),
					(float)c.at("height").ToNumber(),
					(float)c.at("xoffset").ToNumber(),
					(float)c.at("yoffset").ToNumber(),
					(float)c.at("xadvance").ToNumber(),
					(uint32_t)c.at("page").ToInt(),
				});
		}

		const auto& commonJson = fontJson.at("common");
		float lineHeight = commonJson.hasKey("lineHeight") ? (float)commonJson.at("lineHeight").ToNumber() : 0.0f;

		return std::make_shared<Font>(lineHeight, pageTextures, characters);
	}
}
