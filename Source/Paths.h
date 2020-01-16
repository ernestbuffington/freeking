#pragma once

#include <filesystem>

namespace Freeking
{
	class Paths
	{
	public:

		static std::filesystem::path SteamDir();
		static std::filesystem::path SteamGameDir(uint32_t appid);
		static std::filesystem::path KingpinDir();
	};
}
