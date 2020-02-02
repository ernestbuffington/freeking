#include "TimeUtil.h"

namespace Freeking
{
	std::chrono::high_resolution_clock::time_point Time::_timeApplicationStart;
	double Time::_timeSinceApplicationStart;
}
