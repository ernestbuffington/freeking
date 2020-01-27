#include "FontLoader.h"
#include "Font.h"
#include "Texture2D.h"
#include "simdjson.h"
#include "Profiler.h"

namespace Freeking
{
	bool FontLoader::CanLoadExtension(const std::string& extension) const
	{
		if (extension == ".json") return true;

		return false;
	};

	static double get_number(const simdjson::ParsedJson::Iterator& it)
	{
		if (it.is_double()) return it.get_double();
		else if (it.is_integer()) return static_cast<double>(it.get_integer());
		else if (it.is_unsigned_integer()) return static_cast<double>(it.get_unsigned_integer());
		else return 0.0;
	}

	FontLoader::AssetPtr FontLoader::Load(const std::string& name) const
	{
		Profiler pf;
		pf.Start();

		auto buffer = FileSystem::GetFileData(name);
		if (buffer.empty())
		{
			return nullptr;
		}

		auto pj = simdjson::build_parsed_json(buffer.data(), buffer.size());
		if (!pj.is_valid()) return nullptr;

		simdjson::ParsedJson::Iterator pjh(pj);
		if (!pjh.is_object()) return nullptr;

		if (pjh.move_to_key("pages") && pjh.is_array()) pjh.up();
		else return nullptr;

		if (pjh.move_to_key("chars") && pjh.is_array()) pjh.up();
		else return nullptr;

		if (pjh.move_to_key("common") && pjh.is_object()) pjh.up();
		else return nullptr;

		std::vector<std::shared_ptr<Texture2D>> pageTextures;

		if (pjh.move_to_key("pages"))
		{
			if (pjh.down())
			{
				do 
				{
					auto page = pjh.get_string();
					if (auto texture = Texture2D::Library.Get(std::filesystem::path(name).remove_filename().append(page).string()))
					{
						pageTextures.push_back(texture);
					}
				} 
				while (pjh.next() && pjh.is_string());

				pjh.up();
			}

			pjh.up();
		}
		else
		{
			return nullptr;
		}

		std::unordered_map<int32_t, Font::Character> characters;

		if (pjh.move_to_key("chars"))
		{
			if (pjh.down())
			{
				do
				{
					Font::Character c;

					if (pjh.move_to_key("id") && pjh.is_integer()) c.id = pjh.get_integer(); pjh.up();
					if (pjh.move_to_key("x") && pjh.is_number()) c.x = get_number(pjh); pjh.up();
					if (pjh.move_to_key("y") && pjh.is_number()) c.y = get_number(pjh); pjh.up();
					if (pjh.move_to_key("width") && pjh.is_number()) c.width = get_number(pjh); pjh.up();
					if (pjh.move_to_key("height") && pjh.is_number()) c.height = get_number(pjh); pjh.up();
					if (pjh.move_to_key("xoffset") && pjh.is_number()) c.xoffset = get_number(pjh); pjh.up();
					if (pjh.move_to_key("yoffset") && pjh.is_number()) c.yoffset = get_number(pjh); pjh.up();
					if (pjh.move_to_key("xadvance") && pjh.is_number()) c.xadvance = get_number(pjh); pjh.up();
					if (pjh.move_to_key("page") && pjh.is_integer()) c.page = pjh.get_integer(); pjh.up();

					characters.emplace(c.id, std::move(c));
				}
				while (pjh.next() && pjh.is_object());

				pjh.up();
			}

			pjh.up();
		}
		else
		{
			return nullptr;
		}

		float lineHeight = 0.0f;
		if (pjh.move_to_key("common"))
		{
			if (pjh.down())
			{
				if (pjh.move_to_key("lineHeight") && pjh.is_number())
				{
					lineHeight = get_number(pjh);
					pjh.up();
				}

				pjh.up();
			}

			pjh.up();
		}

		pf.Stop("Load Font (" + name + ")");

		return std::make_shared<Font>(lineHeight, pageTextures, characters);
	}
}
