#include "Font.h"
#include "Util.h"
#include "ThirdParty/json/json.hpp"

using json::JSON;

namespace Freeking
{
	Font::Font(float lineHeight,
			   std::vector<std::shared_ptr<Texture2D>> pageTextures,
			   std::unordered_map<int32_t, Character> characters) :
		_lineHeight(lineHeight),
		_pageTextures(std::move(pageTextures)),
		_characters(std::move(characters))
	{
	}

	bool Font::TryGetCharacter(int32_t id, Font::Character& character) const
	{
		auto it = _characters.find(id);
		if (it != _characters.end())
		{
			character = it->second;

			return true;
		}

		return false;
	}
}
