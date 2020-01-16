#include "Game.h"
#include "Window.h"
#include "Input.h"
#include "Matrix4x4.h"
#include "LineRenderer.h"
#include "VertexBinding.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture2D.h"
#include "TextureSampler.h"
#include "BspFile.h"
#include "BspFlags.h"
#include "MdxFile.h"
#include "EntityLump.h"
#include "FpsTimer.h"
#include "FreeCamera.h"
#include "SpriteBatch.h"
#include "Font.h"
#include "Mesh.h"
#include "Util.h"
#include "Map.h"
#include "Lightmap.h"
#include "Paths.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <array>

namespace Freeking
{
	Game::Game(int argc, char** argv)
	{	
		static const std::string windowTitle = "Kingpin";
		_viewportWidth = 1920;
		_viewportHeight = 1080;
		_window = std::make_unique<Window>(windowTitle, _viewportWidth, _viewportHeight);
		_mouseLocked = false;
	}

	Game::~Game()
	{
		_window.reset();
		SDL_Quit();
	}

	void Game::OnResize(int width, int height)
	{
		glViewport(0, 0, width, height);

		_viewportWidth = width;
		_viewportHeight = height;
	}

	void Game::LockMouse(bool lockMouse)
	{
		if (_mouseLocked == lockMouse)
		{
			return;
		}

		_mouseLocked = lockMouse;

		SDL_SetRelativeMouseMode(lockMouse ? SDL_TRUE : SDL_FALSE);

		if (lockMouse)
		{
			int mousePosX, mousePosY;
			SDL_GetMouseState(&mousePosX, &mousePosY);
		}

		int w, h;
		SDL_GetWindowSize(static_cast<SDL_Window*>(*_window), &w, &h);
		SDL_WarpMouseInWindow(static_cast<SDL_Window*>(*_window), w / 2, h / 2);

		Input::ResetMouseDelta();
	}

	void Game::Run()
	{
		uint64_t now = SDL_GetPerformanceCounter();
		uint64_t last = 0;
		double deltaTime = 0.0;
		FpsTimer timer;

		SDL_Event e;
		bool running = true;

		SDL_GetWindowSize(*_window, &_viewportWidth, &_viewportHeight);
		glViewport(0, 0, _viewportWidth, _viewportHeight);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_window->Swap();

		auto lineRenderer = std::make_unique<LineRenderer>(1000000);
		auto spriteBatch = std::make_unique<SpriteBatch>(1000);
		FreeCamera camera;

		bool debug = true;

		std::vector<std::shared_ptr<KeyframeMesh>> mdxMeshes;
		std::array<std::string, 3> mdxNames =
		{
			"body",
			"head",
			"legs",
		};

		for (size_t i = 0; i < mdxNames.size(); ++i)
		{
			auto mdxBuffer = Util::LoadFile("Assets/" + mdxNames[i] + ".mdx");
			auto mdxData = mdxBuffer.data();
			auto& mdxFile = MDXFile::Create(mdxData);

			auto mdxMesh = std::make_shared<KeyframeMesh>();
			mdxFile.Build(mdxData, mdxMesh);
			mdxMesh->SetDiffuse(Util::LoadTexture("Assets/" + mdxNames[i] + "_001.tga"));
			mdxMesh->Commit();

			mdxMeshes.push_back(mdxMesh);
		}

		double frameTime = 0;
		Matrix4x4 modelMatrix;

		auto keyframeShader = Util::LoadShader("Shaders/VertexSkinnedMesh.vert", "Shaders/VertexSkinnedMesh.frag");
		auto font = Util::LoadFont("Assets/roboto-bold.json");
		auto map = std::make_shared<Map>("Assets/sr1.bsp");

		while (running)
		{
			last = now;
			now = SDL_GetPerformanceCounter();
			deltaTime = ((now - last) / (double)SDL_GetPerformanceFrequency());
			timer.Update(deltaTime);

			Input::PreEvent();

			while (SDL_PollEvent(&e))
			{
				switch (e.type)
				{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_WINDOWEVENT:
					if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					{
						OnResize(e.window.data1, e.window.data2);
					}
					break;
				}

				Input::HandleEvent(e);
			}

			LockMouse(Input::IsDown(Button::MouseRight));

			float mouseDeltaX = Input::GetMouseDeltaX();
			float mouseDeltaY = Input::GetMouseDeltaY();

			if (_mouseLocked)
			{
				camera.LookDelta(mouseDeltaX * 0.25f, mouseDeltaY * 0.25f);
			}

			if (Input::JustPressed(Button::KeySPACE))
			{
				debug = !debug;
			}

			if (Input::JustPressed(Button::KeyV))
			{
				modelMatrix = Matrix4x4::Translation(camera.GetPosition()) * Quaternion::FromDegreeAngles(Vector3f(0, camera.GetYaw(), 0)).ToMatrix4x4();
			}

			auto inputForce = Vector3f(0.0f, 0.0f, 0.0f);
			if (Input::IsDown(Button::KeyW)) inputForce += Vector3f(0.0f, 0.0f, 1.0f);
			if (Input::IsDown(Button::KeyS)) inputForce -= Vector3f(0.0f, 0.0f, 1.0f);
			if (Input::IsDown(Button::KeyA)) inputForce += Vector3f(1.0f, 0.0f, 0.0f);
			if (Input::IsDown(Button::KeyD)) inputForce -= Vector3f(1.0f, 0.0f, 0.0f);
			if (inputForce.SquaredLength() > 0.0f)
			{
				inputForce = inputForce.Normalise();
				inputForce *= Input::IsDown(Button::KeyLSHIFT) ? 600.0f : 100.0f;
				camera.Move(inputForce, static_cast<float>(deltaTime));
			}

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glEnable(GL_CULL_FACE);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glCullFace(GL_BACK);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Matrix4x4 projectionMatrix = Matrix4x4::Perspective(80, (float)_viewportWidth / (float)_viewportHeight, 0.1f, 10000.0f);
			Matrix4x4 viewMatrix = camera.GetViewMatrix();
			Matrix4x4 viewProjectionMatrix = projectionMatrix * viewMatrix;

			map->Render(viewProjectionMatrix);

			keyframeShader->Bind();
			keyframeShader->SetUniformValue("diffuse", 0);
			keyframeShader->SetUniformValue("frameVertexBuffer", 1);
			keyframeShader->SetUniformValue("normalBuffer", 2);

			auto frameCount = mdxMeshes.at(0)->GetFrameCount();
			frameTime += (10.0 * deltaTime);
			frameTime = fmod(frameTime, (float)frameCount);

			uint32_t frame = (uint32_t)floor(frameTime);
			frame %= frameCount;
			uint32_t nextFrame = (frame + 1) % frameCount;
			float delta = (float)frameTime - (float)frame;
			delta = Math::Clamp(delta, 0.0f, 1.0f);

			keyframeShader->SetUniformValue("delta", delta);

			for (int i = 0; i < 1; ++i)
			{
				auto m = Matrix4x4::Translation(Vector3f(0, 0, i * 40.0f));
				keyframeShader->SetUniformValue("viewProj", viewProjectionMatrix * (modelMatrix * m));

				for (auto& mdxMesh : mdxMeshes)
				{
					keyframeShader->SetUniformValue("frames[0].index", (int)(frame * mdxMesh->GetFrameVertexCount()));
					keyframeShader->SetUniformValue("frames[0].translate", mdxMesh->FrameTransforms[frame].translate);
					keyframeShader->SetUniformValue("frames[0].scale", mdxMesh->FrameTransforms[frame].scale);

					keyframeShader->SetUniformValue("frames[1].index", (int)(nextFrame * mdxMesh->GetFrameVertexCount()));
					keyframeShader->SetUniformValue("frames[1].translate", mdxMesh->FrameTransforms[nextFrame].translate);
					keyframeShader->SetUniformValue("frames[1].scale", mdxMesh->FrameTransforms[nextFrame].scale);

					mdxMesh->Draw();
				}
			}

			if (debug)
			{
				for (const auto& e : map->Entities())
				{
					Vector3f origin(e.origin.x, e.origin.z, -e.origin.y);
					Vector3f bounds(10, 10, 10);

					Vector2f screenPosition;
					float distance;
					if (Util::WorldPointToNormalisedScreenPoint(origin, screenPosition, projectionMatrix, viewMatrix, 512.0f, distance))
					{
						float alpha = 1.0f - (distance / 512.0f);
						lineRenderer->DrawSphere(origin, 4.0f, 4, 4, Vector4f(0, 1, 1, alpha));
						screenPosition = Util::ScreenSpaceToPixelPosition(screenPosition, Vector4i(0, 0, _viewportWidth, _viewportHeight));
						spriteBatch->DrawText(font.get(), e.classname, screenPosition, Vector4f(1, 1, 1, alpha), 0.25f);
					}
				}

				glDisable(GL_DEPTH_TEST);
				lineRenderer->Flush(viewProjectionMatrix);
				glEnable(GL_DEPTH_TEST);

				auto orthoProjection = Matrix4x4::Ortho(0, (float)_viewportWidth, (float)_viewportHeight, 0, -1.0f, 1.0f);
				spriteBatch->DrawText(font.get(), std::to_string(timer.GetFps()), Vector2f(8, 0), Vector4f(1, 1, 1, 1), 0.5f);
				spriteBatch->Flush(orthoProjection);
			}

			_window->Swap();
		}
	}
}
