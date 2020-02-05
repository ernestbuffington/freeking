#pragma once

#include "LinearColor.h"
#include <stdint.h>

namespace Freeking
{
	class Color
	{
	public:

		Color();
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

		LinearColor ToLinear() const;
		Color WithAlpha(uint8_t alpha);

		uint8_t r, g, b, a;

		static const Color Black;
		static const Color Blue;
		static const Color Clear;
		static const Color Cyan;
		static const Color Grey;
		static const Color Green;
		static const Color Magenta;
		static const Color Red;
		static const Color White;
		static const Color Yellow;
	};
}
