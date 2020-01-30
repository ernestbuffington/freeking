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
#include "Md2/Md2File.h"
#include "EntityLump.h"
#include "FpsTimer.h"
#include "FreeCamera.h"
#include "SpriteBatch.h"
#include "Font.h"
#include "DynamicModel.h"
#include "Util.h"
#include "Map.h"
#include "Paths.h"
#include "Thug.h"
#include "Nav/NavFile.h"
#include "PakFileSystem.h"
#include "Material.h"
#include "Renderer.h"
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
		FileSystem::AddFileSystem(PhysicalFileSystem::Create(std::filesystem::current_path() / "Assets"));
		FileSystem::AddFileSystem(PhysicalFileSystem::Create(Paths::KingpinDir() / "main"));
		FileSystem::AddFileSystem(PakFileSystem::Create(Paths::KingpinDir() / "main/Pak0.pak"));

		static const std::string windowTitle = "Kingpin";
		_viewportWidth = 2880;
		_viewportHeight = 1620;
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


		Renderer renderer;

		std::string mapName("sr1");

		auto lineRenderer = std::make_unique<LineRenderer>(2000000);
		auto spriteBatch = std::make_unique<SpriteBatch>(1000);
		FreeCamera camera;
		bool debug = true;
		auto font = Font::Library.Get("Fonts/Roboto-Bold.json");
		auto map = std::make_shared<Map>(BspFile::Create(FileSystem::GetFileData("maps/" + mapName + ".bsp").data()));

		auto navData = FileSystem::GetFileData("navdata/" + mapName + ".nav");
		auto navNodes = NavFile::ReadNodes(navData.data());

		std::vector<std::shared_ptr<Thug>> thugs;

		for (const auto& e : map->GetEntityLump().Entities)
		{
			if (e.classname.substr(0, 5) == "cast_")
			{
				if (e.classname == "cast_dog")
				{
					continue;
				}

				auto thug = std::make_shared<Thug>(e);
				Vector3f origin(e.origin.x, e.origin.z, -e.origin.y);
				thug->ModelMatrix = Matrix4x4::Translation(origin) * Matrix3x3::RotationY(Math::DegreesToRadians(e.angle));
				camera.MoveTo(origin);

				thugs.push_back(std::move(thug));
			}
		}

		auto globals = std::make_shared<Material::PropertyGlobals>();
		auto md2Shader = Shader::Library.Get("Shaders/DynamicModel.shader");
		auto md2Material = std::make_unique<Material>(md2Shader, globals);
		auto diffuseId = md2Material->GetTextureParameterId("diffuse");
		auto frameVertexBufferId = md2Material->GetTextureParameterId("frameVertexBuffer");

		auto md2Mesh = DynamicModel::Library.Get("models/weapons/g_tomgun/tris.md2");
		auto md2Texture = Texture2D::Library.Get(md2Mesh->Skins[0]);

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

			map->Tick(deltaTime);
			map->Render(viewProjectionMatrix);

			for (const auto& thug : thugs)
			{
				thug->Render(viewProjectionMatrix, deltaTime);
			}

			globals->SetValue("viewProj", viewProjectionMatrix * Matrix4x4::Translation(Vector3f(0, 50, 0)));
			md2Material->SetParameterValue("delta", 0);
			md2Material->SetParameterValue("normalBuffer", DynamicModel::GetNormalBuffer().get());

			if (md2Mesh)
			{
				int md2Frame = 0;
				md2Material->SetParameterValue(diffuseId, md2Texture.get());
				md2Material->SetParameterValue(frameVertexBufferId, md2Mesh->GetFrameVertexBuffer().get());
				md2Material->SetParameterValue("frames[0].index", (int)(md2Frame * md2Mesh->GetFrameVertexCount()));
				md2Material->SetParameterValue("frames[0].translate", md2Mesh->FrameTransforms[md2Frame].translate);
				md2Material->SetParameterValue("frames[0].scale", md2Mesh->FrameTransforms[md2Frame].scale);
				md2Material->SetParameterValue("frames[1].index", (int)(md2Frame * md2Mesh->GetFrameVertexCount()));
				md2Material->SetParameterValue("frames[1].translate", md2Mesh->FrameTransforms[md2Frame].translate);
				md2Material->SetParameterValue("frames[1].scale", md2Mesh->FrameTransforms[md2Frame].scale);
				md2Material->Apply();

				renderer.Draw(md2Mesh->GetBinding().get(), md2Material.get());
			}

			renderer.Flush();

			if (debug)
			{
				for (const auto& e : map->GetEntityLump().Entities)
				{
					Vector3f origin(e.origin.x, e.origin.z, -e.origin.y);
					float distance = origin.LengthBetween(camera.GetPosition());

					if (distance >= 512.0f)
					{
						continue;
					}

					std::string name;
					e.TryGetString("name", name);

					Vector2f screenPosition;
					if (Util::WorldPointToNormalisedScreenPoint(origin, screenPosition, projectionMatrix, viewMatrix, 512.0f))
					{
						float alpha = 1.0f - (distance / 512.0f);
						lineRenderer->DrawSphere(origin, 4.0f, 4, 4, Vector4f(0, 1, 1, alpha));
						screenPosition = Util::ScreenSpaceToPixelPosition(screenPosition, Vector4i(0, 0, _viewportWidth, _viewportHeight));
						screenPosition.x = (int)screenPosition.x;
						screenPosition.y = (int)screenPosition.y;
						auto text = e.classname + " (" + name + ")";
						spriteBatch->DrawText(font.get(), text, screenPosition + Vector2f(2, 2), Vector4f(0, 0, 0, alpha), 0.5f);
						spriteBatch->DrawText(font.get(), text, screenPosition, Vector4f(1, 1, 1, alpha), 0.5f);
					}
				}

				for (int i = 0; i < navNodes.size(); ++i)
				{
					const auto& navpoint = navNodes[i];
					auto origin = Vector3(navpoint.Position.y, navpoint.Position.w, -navpoint.Position.z);

					float distance = origin.LengthBetween(camera.GetPosition());

					if (distance >= 512.0f)
					{
						continue;
					}

					Vector2f screenPosition;
					if (Util::WorldPointToNormalisedScreenPoint(origin, screenPosition, projectionMatrix, viewMatrix, 512.0f))
					{
						float alpha = 1.0f - (distance / 512.0f);
						lineRenderer->DrawAABBox(origin, Vector3f(-5, -5, -5), Vector3f(5, 5, 5), Vector4f(0, 1, 0, alpha));
						screenPosition = Util::ScreenSpaceToPixelPosition(screenPosition, Vector4i(0, 0, _viewportWidth, _viewportHeight));
						screenPosition.x = (int)screenPosition.x;
						screenPosition.y = (int)screenPosition.y;
						auto text = "node #" + std::to_string(i);
						spriteBatch->DrawText(font.get(), text, screenPosition + Vector2f(2, 2), Vector4f(0, 0, 0, alpha), 0.5f);
						spriteBatch->DrawText(font.get(), text, screenPosition, Vector4f(1, 1, 1, alpha), 0.5f);
					}
				}

				glDisable(GL_DEPTH_TEST);
				lineRenderer->Flush(viewProjectionMatrix);
				glEnable(GL_DEPTH_TEST);

				auto fps = timer.GetFps();
				Vector4f fpsColor = Vector4f(0, 1, 0, 1);

				if (fps < 30)
				{
					fpsColor = Vector4f(1, 0, 0, 1);
				}
				else if (fps < 60)
				{
					fpsColor = Vector4f(1, 1, 0, 1);
				}

				auto orthoProjection = Matrix4x4::Ortho(0, (float)_viewportWidth, (float)_viewportHeight, 0, -1.0f, 1.0f);
				spriteBatch->DrawText(font.get(), std::to_string(fps), Vector2f(10, 2), Vector4f(0, 0, 0, 1), 1.0f);
				spriteBatch->DrawText(font.get(), std::to_string(fps), Vector2f(8, 0), fpsColor, 1.0f);
				spriteBatch->Flush(orthoProjection);
			}

			_window->Swap();
		}
	}
}
