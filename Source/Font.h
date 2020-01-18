#pragma once

#include <unordered_map>
#include <memory>
#include <vector>

namespace json
{
	class JSON;
}

namespace Freeking
{
	class Texture2D;

	class Font
	{
	public:

		struct Character
		{
			uint32_t id;
			float x;
			float y;
			float width;
			float height;
			float xoffset;
			float yoffset;
			float xadvance;
			uint32_t page;
		};

		Font(float lineHeight,
			 std::vector<std::shared_ptr<Texture2D>> pageTextures,
			 std::unordered_map<int32_t, Character> characters);

		bool TryGetCharacter(int32_t id, Character& character) const;

		Texture2D* GetPageTexture(std::size_t index) const { return _pageTextures.at(index).get(); }
		float GetLineHeight() const { return _lineHeight; }

	private:

		float _lineHeight;
		std::vector<std::shared_ptr<Texture2D>> _pageTextures;
		std::unordered_map<int32_t, Character> _characters;
	};
}
