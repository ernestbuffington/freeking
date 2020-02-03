#pragma once

#include "Vector.h"
#include <vector>

namespace Freeking
{
	enum class NavFlag : uint8_t
	{
		Jump = 0x01,
		Land = 0x02,
		Platform = 0x04,
		Teleport = 0x08,
	};

	struct NavNode
	{
		Vector4f Position;
		std::vector<NavFlag> NodeFlags;
	};

	struct NavFile
	{
		static std::vector<NavNode> ReadNodes(const uint8_t* data);
	};
}
