#pragma once

namespace Freeking
{
	class FpsTimer
	{
	public:

		FpsTimer();

		void Update(double time);

		inline int GetFps() const { return _fps; }
		inline double GetFrameTime() const { return _frameTime; }

	private:

		int _fps;
		double _oldFps;
		int _frameCount;
		double _frameTime;
	};
}

