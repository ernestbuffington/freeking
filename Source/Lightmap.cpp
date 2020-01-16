#include "Lightmap.h"

namespace Freeking
{
	LightmapImage::LightmapImage(int width, int height) :
		_width(width), _height(height)
	{
		Data.resize((width * height) * 3);
	}

	LightmapNode::LightmapNode(int x, int y, int width, int height) :
		_x(x),
		_y(y),
		_width(width),
		_height(height),
		_filled(false),
		_a(nullptr),
		_b(nullptr)
	{
	}

	std::shared_ptr<LightmapNode> LightmapNode::Allocate(std::shared_ptr<LightmapNode>& parent, int width, int height)
	{
		if (parent->_a && parent->_b)
		{
			auto a = Allocate(parent->_a, width, height);
			if (a)
			{
				return a;
			}

			return Allocate(parent->_b, width, height);
		}

		if (parent->_filled)
		{
			return nullptr;
		}

		if (parent->_width < width || parent->_height < height)
		{
			return nullptr;
		}

		if (parent->_width == width && parent->_height == height)
		{
			parent->_filled = true;

			return parent;
		}

		if ((parent->_width - width) > (parent->_height - height))
		{
			parent->_a = std::make_shared<LightmapNode>(parent->_x, parent->_y, width, parent->_height);
			parent->_b = std::make_shared<LightmapNode>(parent->_x + width, parent->_y, parent->_width - width, parent->_height);
		}
		else
		{
			parent->_a = std::make_shared<LightmapNode>(parent->_x, parent->_y, parent->_width, height);
			parent->_b = std::make_shared<LightmapNode>(parent->_x, parent->_y + height, parent->_width, parent->_height - height);
		}

		return Allocate(parent->_a, width, height);
	}
}
