#pragma once

#include <memory>
#include <vector>

namespace Freeking
{
	class LightmapImage
	{
	public:

		LightmapImage(int width, int height);

		void Insert(int rectX, int rectY, int width, int height, const uint8_t* buffer);

		inline int GetWidth() const { return _width; }
		inline int GetHeight() const { return _height; }

		std::vector<uint8_t> Data;

	private:

		int _width;
		int _height;
	};
}

