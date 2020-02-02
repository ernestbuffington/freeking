#pragma once

#include <math.h>

namespace Freeking
{
	struct Math
	{
		static const float Pi;
		static const float HalfPi;
		static const float QuarterPi;
		static const float TwoPi;
		static const float Epsilon;
		static const float GoldenRatio;
		static const float GoldenRatioConjugate;
		static const double Log2E;

		static inline float RadiansToDegrees(float radians) { return radians * (180.0f / Pi); }
		static inline float DegreesToRadians(float degrees) { return degrees * (Pi / 180.0f); }

		static inline float Abs(float v) { return fabsf(v); }
		static inline float Mod(float a, float b) { return fmodf(a, b); }
		static inline float Sin(float a) { return sinf(a); }
		static inline float Cos(float a) { return cosf(a); }
		static inline float Round(float a) { return roundf(a); }

		static inline float SineWave(float v) { return Clamp((Sin(v) + 1.0f) * 0.5f, 0.0f, 1.0f); }

		static float SineWave(float time, float speed)
		{
			return SineWave(AngleAtTime(time, speed));
		}

		static float AngleAtTime(float time, float speed)
		{
			return fmodf(time, TwoPi * (speed > 0.0f ? (1.0f / speed) : 0.0f)) * speed;
		}

		static float Lerp(float a, float b, float f)
		{
			return a + f * (b - a);
		}

		static inline bool FloatEqual(float a, float b, float tolerance = Epsilon) { return Abs(a - b) <= tolerance; }

		static inline float Sign(float a)
		{
			if (a > 0.0f) return 1.0f;
			if (a < 0.0f) return -1.0f;

			return 0.0f;
		}

		template<typename T>
		static inline T Min(T a, T b) { return (a < b) ? a : b; }

		template<typename T>
		static inline T Max(T a, T b) { return (a > b) ? a : b; }

		template<typename T>
		static inline T Clamp(T value, T min, T max) { return Max(Min(value, max), min); }
	};
}
