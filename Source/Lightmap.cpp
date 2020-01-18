#include "Lightmap.h"

namespace Freeking
{
	LightmapImage::LightmapImage(int width, int height) :
		_width(width), _height(height)
	{
		Data.resize((width * height) * 3);
	}
}
