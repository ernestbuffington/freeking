#include "Util.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "Font.h"
#include "FileSystem.h"
#include <charconv>
#include <filesystem>
#include <fstream> 

#include "json.hpp"
using json::JSON;

namespace Freeking
{
	std::shared_ptr<ShaderProgram> Util::LoadShader(const std::string& vertPath, const std::string& fragPath)
	{
		auto vertSource = FileSystem::GetFileData(vertPath);
		auto fragSource = FileSystem::GetFileData(fragPath);

		if (vertSource.empty() || fragSource.empty())
		{
			return nullptr;
		}

		return std::make_shared<ShaderProgram>(
			std::string(vertSource.data(), vertSource.size()),
			std::string(fragSource.data(), fragSource.size()));
	}

	std::shared_ptr<Font> Util::LoadFont(const std::string& path)
	{
		auto fontBuffer = FileSystem::GetFileData(path);
		if (fontBuffer.empty())
		{
			return nullptr;
		}

		auto fontString = std::string(fontBuffer.data(), fontBuffer.size());
		auto fontJson = JSON::Load(fontString);

		std::vector<std::shared_ptr<Texture2D>> pageTextures;
		std::unordered_map<int32_t, Font::Character> characters;

		auto pages = fontJson["pages"];
		for (int i = 0; i < pages.size(); ++i)
		{
			std::filesystem::path fontPath(path);
			fontPath = fontPath.remove_filename();
			pageTextures.push_back(Texture2D::Library.Get(fontPath.append(pages[i].ToString()).string()));
		}

		auto chars = fontJson["chars"];
		for (int i = 0; i < chars.size(); ++i)
		{
			auto& c = chars[i];
			characters.emplace(
				c["id"].ToInt(),
				Font::Character
				{
					(uint32_t)c["id"].ToInt(),
					(float)c["x"].ToNumber(),
					(float)c["y"].ToNumber(),
					(float)c["width"].ToNumber(),
					(float)c["height"].ToNumber(),
					(float)c["xoffset"].ToNumber(),
					(float)c["yoffset"].ToNumber(),
					(float)c["xadvance"].ToNumber(),
					(uint32_t)c["page"].ToInt(),
				});
		}

		float lineHeight = (float)fontJson["common"]["lineHeight"].ToNumber();

		return std::make_shared<Font>(lineHeight, pageTextures, characters);
	}

	Vector2f Util::ScreenSpaceToPixelPosition(const Vector2f& point, const Vector4i& viewport)
	{
		return Vector2f(
			viewport.x + ((point.x * 0.5f + 0.5f) * viewport.z),
			viewport.y + (viewport.w - ((point.y * 0.5f + 0.5f) * viewport.w)));
	}

	bool Util::WorldPointToNormalisedScreenPoint(const Vector3f& position, Vector2f& result, const Matrix4x4& projectionMatrix, const Matrix4x4& viewMatrix, float maxDistance)
	{
		Vector4f in(position.x, position.y, position.z, 1.0f);
		in = projectionMatrix * (viewMatrix * in);

		if (in.w < 0.001f || in.w > maxDistance)
		{
			return false;
		}

		in.w = 1.0f / in.w;
		in *= in.w;

		result = Vector2f(in.x, in.y);

		return true;
	}

	bool Util::TryParseFloat(const std::string& s, float& v)
	{
		return std::from_chars(s.data(), s.data() + s.size(), v, std::chars_format::general).ec == std::errc();
	}

	bool Util::TryParseInt(const std::string& s, int& v)
	{
		return std::from_chars(s.data(), s.data() + s.size(), v).ec == std::errc();
	}
}
