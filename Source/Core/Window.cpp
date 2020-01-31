#include "Window.h"
#include <glad/gl.h>
#include <iostream>

namespace Freeking
{
	Window::Window(const std::string& title, const int width, const int height)
	{
		SDL_version compiledVersion, linkedVersion;
		SDL_VERSION(&compiledVersion);
		SDL_GetVersion(&linkedVersion);

		std::clog << "Initializing SDL..." << std::endl;
		std::clog << "SDL Version/Compiled " << uint32_t(compiledVersion.major) << "." <<
			uint32_t(compiledVersion.minor) << "." << uint32_t(compiledVersion.patch) << std::endl;
		std::clog << "SDL Version/Linked " << uint32_t(linkedVersion.major) << "." <<
			uint32_t(linkedVersion.minor) << "." << uint32_t(linkedVersion.patch) << std::endl;

		if (SDL_WasInit(0) == 0)
		{
			SDL_SetMainReady();

			if (SDL_Init(0) != 0)
			{
				throw std::runtime_error("Could not initialize SDL: " + std::string(SDL_GetError()));
			}

			if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
			{
				throw std::runtime_error("Could not initialize SDL Video Subsystem: " + std::string(SDL_GetError()));
			}

			if (SDL_InitSubSystem(SDL_INIT_TIMER) != 0)
			{
				throw std::runtime_error("Could not initialize SDL Timer Subsystem: " + std::string(SDL_GetError()));
			}
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		const uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE;

		if (auto window = std::unique_ptr<SDL_Window, SDLDestroyer>(SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			flags));
			window != nullptr)
		{
			_window = std::move(window);
		}
		else
		{
			throw std::runtime_error("Failed creating window: " + std::string(SDL_GetError()));
		}
		
		if (auto renderer = SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED);
			renderer != nullptr)
		{
			_renderer = std::move(std::unique_ptr<SDL_Renderer, SDLDestroyer>(renderer));
		}
		else
		{
			throw std::runtime_error("SDL2 Renderer couldn't be created: " + std::string(SDL_GetError()));
		}
	
		if (auto context = SDL_GL_CreateContext(_window.get());
			context != nullptr)
		{
			_glContext = std::move(std::unique_ptr<SDL_GLContext, SDLDestroyer>(&context));
		}
		else
		{
			throw std::runtime_error("Failed to initialize the OpenGL context: " + std::string(SDL_GetError()));
		}

		if (!gladLoaderLoadGL())
		{
			throw std::runtime_error("Failed to initialize the OpenGL context.");
		}

		std::cout << "OpenGL loaded" << "\n" <<
			"Vendor: " << glGetString(GL_VENDOR) << "\n" <<
			"Renderer: " << glGetString(GL_RENDERER) << "\n" <<
			"Version: " << glGetString(GL_VERSION) << "\n" <<
			std::endl;

		if (!GLAD_GL_VERSION_4_6)
		{
			throw std::runtime_error("Your OpenGL version is too low, expected 4.6 or higher.");
		}

		SDL_GL_SetSwapInterval(0);
		SDL_ShowWindow(_window.get());
	}

	void Window::SetTitle(const std::string& title)
	{
		SDL_SetWindowTitle(_window.get(), title.c_str());
	}

	const std::string Window::GetTitle() const
	{
		return SDL_GetWindowTitle(_window.get());
	}

	void Window::Swap()
	{
		SDL_GL_SwapWindow(_window.get());
	}
}
