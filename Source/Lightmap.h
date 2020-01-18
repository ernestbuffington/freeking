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

		static int Allocate(int parentIndex, int width, int height);

		inline int GetX() const { return _x; }
		inline int GetY() const { return _y; }
		inline int GetWidth() const { return _width; }
		inline int GetHeight() const { return _height; }

		static int NewNode(int x, int y, int width, int height);
		inline static const LightmapNode& GetNode(int index) { return NodePool.at(index); }

	private:

		static std::vector<LightmapNode> NodePool;
		static int CurrentNodeIndex;

		int _x;
		int _y;
		int _width;
		int _height;
		bool _filled;
		int _a;
		int _b;
	};
}

