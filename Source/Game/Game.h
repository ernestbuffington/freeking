#pragma once

#include <memory>
#include <string>
#include <filesystem>
#include "PakFile.h"

namespace Freeking
{
	class Game
	{
	public:

		Game(int argc, char** argv);
		~Game();

		void Run();

	private:

		void OnResize(int width, int height);
		void LockMouse(bool lockMouse);

		std::unique_ptr<class Window> _window;

		int _viewportWidth;
		int _viewportHeight;

		bool _mouseLocked;
	};
}
