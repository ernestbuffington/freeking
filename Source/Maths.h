#pragma once

namespace Freeking
{
	namespace Math
	{
		const float PI = 3.1415926f;
		const float HALF_PI = PI / 2.0f;
		const float QUARTER_PI = PI / 4.0f;
		const float TWO_PI = PI * 2.0f;
		const float EPSILON = 0.00001f;
		const float GOLDEN_RATIO = 1.61803398875f;
		const float GOLDEN_RATIO_CONJUGATE = 1.0f / GOLDEN_RATIO;
		const double LOG_2_E = 1.4426950408889634074;

		inline float RadiansToDegrees(float radians) { return radians * 180.0f / PI; }
		inline float DegreesToRadians(float degrees) { return degrees * PI / 180.0f; }

		inline bool FloatEqual(float a, float b)
		{
			const float c = a - b;

			return (c < EPSILON && c > -EPSILON);
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
