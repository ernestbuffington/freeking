#include "Color.h"

namespace Freeking
{
	const Color Color::Black(0, 0, 0);
	const Color Color::Blue(0, 0, 255);
	const Color Color::Clear(0, 0, 0, 0);
	const Color Color::Cyan(0, 255, 255);
	const Color Color::Grey(128, 128, 128);
	const Color Color::Green(0, 255, 0);
	const Color Color::Magenta(255, 0, 255);
	const Color Color::Red(255, 0, 0);
	const Color Color::White(255, 255, 255);
	const Color Color::Yellow(255, 255, 0);

	Color::Color() :
		r(255), g(255), b(255), a(255)
	{
	}

	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
		r(r), g(g), b(b), a(a)
	{
	}

	LinearColor Color::ToLinear() const
	{
		return LinearColor::Colour255(r, g, b, a);
	}

	Color Color::WithAlpha(uint8_t alpha)
	{
		return Color(r, g, b, alpha);
	}
}
