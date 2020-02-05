#pragma once

#include <stdint.h>

namespace Freeking
{
	class LinearColor
	{
	public:

		LinearColor();
		LinearColor(float r, float g, float b, float a = 1.0f);

		LinearColor WithAlpha(float alpha);

		static LinearColor Colour255(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		static LinearColor ColourHSV(float h, float s, float v, float a = 1.0f);
		static LinearColor Lerp(const LinearColor& a, const LinearColor& b, float t);

		float r, g, b, a;

		static const LinearColor Black;
		static const LinearColor Blue;
		static const LinearColor Clear;
		static const LinearColor Cyan;
		static const LinearColor Grey;
		static const LinearColor Green;
		static const LinearColor Magenta;
		static const LinearColor Red;
		static const LinearColor White;
		static const LinearColor Yellow;
	};
}
