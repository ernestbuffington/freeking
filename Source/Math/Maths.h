#pragma once

namespace Freeking
{
	namespace Math
	{
		const float Pi = 3.1415926f;
		const float HalfPi = Pi / 2.0f;
		const float QuarterPi = Pi / 4.0f;
		const float TwoPi = Pi * 2.0f;
		const float Epsilon = 0.00001f;
		const float GoldenRatio = 1.61803398875f;
		const float GoldenRatioConjugate = 1.0f / GoldenRatio;
		const double Log2E = 1.4426950408889634074;

		inline float RadiansToDegrees(float radians) { return radians * 180.0f / Pi; }
		inline float DegreesToRadians(float degrees) { return degrees * Pi / 180.0f; }

		inline bool FloatEqual(float a, float b)
		{
			const float c = a - b;

			return (c < Epsilon && c > -Epsilon);
		}

		inline float Sign(float a)
		{
			if (a > 0.0f) return 1.0f;
			if (a < 0.0f) return -1.0f;

			return 0.0f;
		}

		template<typename T>
		inline T Min(T a, T b) { return (a < b) ? a : b; }

		template<typename T>
		inline T Max(T a, T b) { return (a > b) ? a : b; }

		template<typename T>
		inline T Clamp(T value, T min, T max) { return Max(Min(value, max), min); }
	}
}
