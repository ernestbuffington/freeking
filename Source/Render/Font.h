#pragma once

#include "AssetLibrary.h"
#include <unordered_map>
#include <memory>
#include <vector>

namespace Freeking
{
	class Font;
	class Texture2D;

	class FontLibrary : public AssetLibrary<Font>
	{
	protected:

		virtual void UpdateLoaders() override;
	};

	class Font
	{
	public:

		static FontLibrary Library;

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

		Font(float lineHeight, std::vector<std::shared_ptr<Texture2D>> pageTextures, std::unordered_map<int32_t, Character> characters);

		bool TryGetCharacter(int32_t id, Character& character) const;

		Texture2D* GetPageTexture(std::size_t index) const { return _pageTextures.at(index).get(); }
		float GetLineHeight() const { return _lineHeight; }

	private:

		float _lineHeight;
		std::vector<std::shared_ptr<Texture2D>> _pageTextures;
		std::unordered_map<int32_t, Character> _characters;
	};
}
