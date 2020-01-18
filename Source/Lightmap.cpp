#include "Lightmap.h"

namespace Freeking
{
	std::vector<LightmapNode> LightmapNode::NodePool = std::vector<LightmapNode>(65536);
	int LightmapNode::CurrentNodeIndex = 0;

	LightmapImage::LightmapImage(int width, int height) :
		_width(width), _height(height)
	{
		Data.resize((width * height) * 3);
	}

	int LightmapNode::NewNode(int x, int y, int width, int height)
	{
		auto& node = NodePool[CurrentNodeIndex];
		node._x = x;
		node._y = y;
		node._width = width;
		node._height = height;
		node._filled = false;
		node._a = -1;
		node._b = -1;

		return CurrentNodeIndex++;
	}

	int LightmapNode::Allocate(int parentIndex, int width, int height)
	{
		auto& parent = NodePool[parentIndex];

		if (parent._a != -1 || parent._b != -1)
		{
			auto a = Allocate(parent._b, width, height);
			if (a != -1)
			{
				return a;
			}

			return Allocate(parent._a, width, height);
		}

		if (parent._filled)
		{
			return -1;
		}
		else if (parent._width < width || parent._height < height)
		{
			return -1;
		}
		else if (parent._width == width && parent._height == height)
		{
			parent._filled = true;

			return parentIndex;
		}
		else if ((parent._width - width) > (parent._height - height))
		{
			parent._a = NewNode(parent._x, parent._y, width, parent._height);
			parent._b = NewNode(parent._x + width, parent._y, parent._width - width, parent._height);
		}
		else
		{
			parent._a = NewNode(parent._x, parent._y, parent._width, height);
			parent._b = NewNode(parent._x, parent._y + height, parent._width, parent._height - height);
		}

		return Allocate(parent._a, width, height);
	}
}
