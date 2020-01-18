#pragma once

#include <chrono>
#include <iostream>

namespace Freeking
{
	class Profiler
	{
	public:

		void Start()
		{
			begin = std::chrono::steady_clock::now();
		}

		void Stop(std::string s)
		{
			auto end = std::chrono::steady_clock::now();
			std::cout << s.c_str() << " time elapsed = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1e6 << "s" << std::endl;
		}

	private:

		std::chrono::steady_clock::time_point begin;
	};
}

