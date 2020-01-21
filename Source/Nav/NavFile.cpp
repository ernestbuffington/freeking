#include "NavFile.h"

namespace Freeking
{
	std::vector<NavNode> NavFile::ReadNodes(const char* data)
	{
		if (*(uint16_t*)&data[0] != 4)
		{
			return {};
		}

		size_t pos = 4;
		uint16_t numNodes = *(uint16_t*)&data[pos];
		pos += 2;

		std::vector<NavNode> nodes(numNodes);

		for (int i = 0; i < numNodes; ++i)
		{
			NavNode& node = nodes[i];
			node.Position = *(Vector4f*)&data[pos];
			pos += 16;
			pos += 52; // what's this data

			for (int j = 0; j < numNodes; ++j)
			{
				node.NodeFlags.emplace_back((NavFlag)((j % 2 == 0) ? data[pos + (j / 2)] >> 4 : data[pos + (j / 2)] & 0x0F));
			}

			pos += (numNodes + 1) / 2;
		}

		return nodes;
	}
}
