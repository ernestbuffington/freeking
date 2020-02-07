#include "LinearColor.h"
#include "Maths.h"

namespace Freeking
{
	const LinearColor LinearColor::Black(0, 0, 0);
	const LinearColor LinearColor::Blue(0, 0, 1);
	const LinearColor LinearColor::Clear(0, 0, 0, 0);
	const LinearColor LinearColor::Cyan(0, 1, 1);
	const LinearColor LinearColor::Grey(0.5f, 0.5f, 0.5f);
	const LinearColor LinearColor::Green(0, 1, 0);
	const LinearColor LinearColor::Magenta(1, 0, 1);
	const LinearColor LinearColor::Red(1, 0, 0);
	const LinearColor LinearColor::White(1, 1, 1);
	const LinearColor LinearColor::Yellow(1, 1, 0);

	LinearColor::LinearColor() :
		r(1.0f), g(1.0f), b(1.0f), a(1.0f)
	{
	}

	LinearColor::LinearColor(float r, float g, float b, float a) :
		r(r), g(g), b(b), a(a)
	{
	}

	LinearColor LinearColor::WithAlpha(float alpha) const
	{
		return LinearColor(r, g, b, alpha);
	}

	LinearColor LinearColor::Colour255(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		return LinearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}

	LinearColor LinearColor::ColourHSV(float h, float s, float v, float a)
	{
		float r = 0;
		float g = 0;
		float b = 0;

		int i = (int)floor(h * 6);
		float f = h * 6 - i;
		float p = v * (1 - s);
		float q = v * (1 - f * s);
		float t = v * (1 - (1 - f) * s);

		switch (i % 6)
		{
		case 0: r = v, g = t, b = p; break;
		case 1: r = q, g = v, b = p; break;
		case 2: r = p, g = v, b = t; break;
		case 3: r = p, g = q, b = v; break;
		case 4: r = t, g = p, b = v; break;
		case 5: r = v, g = p, b = q; break;
		}

		return LinearColor(r, g, b, a);
	}

	LinearColor LinearColor::Lerp(const LinearColor& a, const LinearColor& b, float t)
	{
		return LinearColor(
			Math::Lerp(a.r, b.r, t),
			Math::Lerp(a.g, b.g, t),
			Math::Lerp(a.b, b.b, t),
			Math::Lerp(a.a, b.a, t));
	}
}
