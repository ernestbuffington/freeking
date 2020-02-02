#pragma once

#include <chrono>

namespace Freeking
{
	class Time
	{

	public:

		Time() = delete;
		~Time() = delete;

		static void Update()
		{
			auto timeNow = std::chrono::high_resolution_clock::now();
			_timeSinceApplicationStart = std::chrono::duration_cast<std::chrono::duration<double>>(timeNow - _timeApplicationStart).count();
		}

		inline static double Now() { return _timeSinceApplicationStart; }

		static void SetTimeApplicationStart() { _timeApplicationStart = std::chrono::high_resolution_clock::now(); }

	private:


		static std::chrono::high_resolution_clock::time_point _timeApplicationStart;
		static double _timeSinceApplicationStart;
	};
}

