#pragma once

#include <memory>
#include <vector>

namespace Freeking
{
	class LightmapImage
	{
	public:

		LightmapImage(int width, int height);

		inline int GetWidth() const { return _width; }
		inline int GetHeight() const { return _height; }

		std::vector<uint8_t> Data;

	private:

		int _width;
		int _height;
	};

	class LightmapNode
	{
	public:

		LightmapNode(int x, int y, int width, int height);

		static std::shared_ptr<LightmapNode> Allocate(std::shared_ptr<LightmapNode>& parent, int width, int height);

		inline int GetX() const { return _x; }
		inline int GetY() const { return _y; }
		inline int GetWidth() const { return _width; }
		inline int GetHeight() const { return _height; }

	private:

		int _x;
		int _y;
		int _width;
		int _height;
		bool _filled;
		std::shared_ptr<LightmapNode> _a;
		std::shared_ptr<LightmapNode> _b;
	};
}

