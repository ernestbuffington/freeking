#include "FpsTimer.h"

namespace Freeking
{
	FpsTimer::FpsTimer() :
		_fps(0),
		_oldFps(0.0),
		_frameCount(0),
		_frameTime(0.0)
	{
	}

	void FpsTimer::Update(double time)
	{
		++_frameCount;

		_frameTime = time;
		_oldFps += time;

		if (_oldFps >= 1.0)
		{
			_fps = _frameCount;
			_frameCount = 0;
			_oldFps = 0.0;
		}
	}
}
