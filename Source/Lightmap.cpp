#include "Lightmap.h"

namespace Freeking
{
	LightmapImage::LightmapImage(int width, int height) :
		_width(width), _height(height)
	{
		Data.resize((width * height) * 3);
	}

	void LightmapImage::Insert(int rectX, int rectY, int width, int height, const uint8_t* buffer)
	{
		if (height <= 0 || width <= 0)
		{
			return;
		}

		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y)
			{
				int dstPixel = ((rectY + y) * _width) + (rectX + x);
				int dstIndex = dstPixel * 3;
				int srcPixel = (y * width) + x;
				int srcIndex = (srcPixel * 3);

				Data[dstIndex] = buffer[srcIndex];
				Data[dstIndex + 1] = buffer[srcIndex + 1];
				Data[dstIndex + 2] = buffer[srcIndex + 2];
			}
		}
	}
}
