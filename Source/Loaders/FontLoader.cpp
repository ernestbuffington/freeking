#include "FontLoader.h"
#include "Font.h"
#include "Texture2D.h"
#include "json.hpp"
#include "Profiler.h"
#include <array>

namespace Freeking
{
	using json = nlohmann::json;

	bool FontLoader::CanLoadExtension(const std::string& extension) const
	{
		if (extension == ".json") return true;

		return false;
	};

	FontLoader::AssetPtr FontLoader::Load(const std::string& name) const
	{
		Profiler pf;
		pf.Start();

		auto buffer = FileSystem::GetFileData(name);
		if (buffer.empty())
		{
			return nullptr;
		}

		auto j = json::parse(buffer);
		if (!j.is_object())
		{
			return nullptr;
		}

		if (!j.contains("pages") ||
			!j.contains("chars") ||
			!j.contains("common"))
		{
			return nullptr;
		}

		const auto& jPages = j["pages"];
		const auto& jChars = j["chars"];
		const auto& jCommon = j["common"];

		if (!jPages.is_array() ||
			!jChars.is_array() ||
			!jCommon.is_object())
		{
			return nullptr;
		}

		if (!jCommon.contains("lineHeight"))
		{
			return nullptr;
		}
		else
		{
			if (!jCommon["lineHeight"].is_number())
			{
				return nullptr;
			}
		}

		for (const auto& jPage : jPages)
		{
			if (!jPage.is_string())
			{
				return nullptr;
			}
		}

		auto numPages = jPages.size();

		for (const auto& jChar : jChars)
		{
			if (!jChar.contains("id") ||
				!jChar.contains("x") ||
				!jChar.contains("y") ||
				!jChar.contains("width") ||
				!jChar.contains("height") ||
				!jChar.contains("xoffset") ||
				!jChar.contains("yoffset") ||
				!jChar.contains("xadvance") ||
				!jChar.contains("page"))
			{
				return nullptr;
			}

			if (!jChar["id"].is_number_unsigned() ||
				!jChar["x"].is_number() ||
				!jChar["y"].is_number() ||
				!jChar["width"].is_number() ||
				!jChar["height"].is_number() ||
				!jChar["xoffset"].is_number() ||
				!jChar["yoffset"].is_number() ||
				!jChar["xadvance"].is_number() ||
				!jChar["page"].is_number_unsigned())
			{
				return nullptr;
			}

			if (const auto& page = jChar["page"].get<uint32_t>();
				page >= numPages)
			{
				return nullptr;
			}
		}

		auto path = std::filesystem::path(name).remove_filename();
		std::vector<std::shared_ptr<Texture2D>> pageTextures;

		for (const auto& jPage : jPages)
		{
			auto pagePath = path.append(jPage.get<std::string>()).string();
			if (!FileSystem::FileExists(pagePath))
			{
				return nullptr;
			}

			if (auto texture = Texture2D::Library.Get(pagePath))
			{
				pageTextures.push_back(texture);
			}
			else
			{
				return nullptr;
			}
		}

		std::unordered_map<int32_t, Font::Character> characters;

		for (const auto& jChar : jChars)
		{
			characters.emplace(jChar["id"].get<uint32_t>(),
				Font::Character
				{
					jChar["x"].get<float>(),
					jChar["y"].get<float>(),
					jChar["width"].get<float>(),
					jChar["height"].get<float>(),
					jChar["xoffset"].get<float>(),
					jChar["yoffset"].get<float>(),
					jChar["xadvance"].get<float>(),
					jChar["page"].get<uint32_t>(),
				});
		}

		float lineHeight = jCommon["lineHeight"].get<float>();

		pf.Stop("Load Font (" + name + ")");

		return std::make_shared<Font>(lineHeight, pageTextures, characters);
	}
}
