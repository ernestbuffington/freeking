#include "Util.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "Font.h"
#include <charconv>
#include <filesystem>
#include <fstream> 

#define STB_IMAGE_IMPLEMENTATION
#include "../ThirdParty/stb/stb_image.h"

#include "../ThirdParty/json.hpp"
using json::JSON;

namespace Freeking
{
	std::vector<char> Util::LoadFile(const std::string& filepath)
	{
		std::ifstream ifs(filepath, std::ios::binary | std::ios::ate);

		auto end = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		auto size = std::size_t(end - ifs.tellg());

		if (size == 0)
		{
			return {};
		}

		std::vector<char> buffer(size);
		ifs.read((char*)buffer.data(), buffer.size());

		return buffer;
	}

	std::shared_ptr<Texture2D> Util::LoadTexture(const std::string& path)
	{
		auto buffer = LoadFile(path);
		auto data = buffer.data();

		int imageWidth;
		int imageHeight;
		int imageChannels;
		uint8_t* image = stbi_load_from_memory((uint8_t*)data, (std::int32_t)buffer.size(), &imageWidth, &imageHeight, &imageChannels, 0);

		auto texture = std::make_shared<Texture2D>(
			imageWidth,
			imageHeight,
			GL_RGBA,
			imageChannels == 3 ? GL_RGB : GL_RGBA,
			GL_UNSIGNED_BYTE,
			image);

		stbi_image_free(image);

		return texture;
	}

	std::shared_ptr<ShaderProgram> Util::LoadShader(const std::string& vertPath, const std::string& fragPath)
	{
		auto vertSource = LoadFile(vertPath);
		auto fragSource = LoadFile(fragPath);

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
		auto fontBuffer = Util::LoadFile(path);
		auto fontString = std::string(fontBuffer.data(), fontBuffer.size());
		auto fontJson = JSON::Load(fontString);

		std::vector<std::shared_ptr<Texture2D>> pageTextures;
		std::map<int32_t, Font::Character> characters;

		auto pages = fontJson["pages"];
		for (int i = 0; i < pages.size(); ++i)
		{
			std::filesystem::path fontPath(path);
			fontPath = fontPath.remove_filename();
			pageTextures.push_back(Util::LoadTexture(fontPath.append(pages[i].ToString()).string()));
		}

		auto chars = fontJson["chars"];
		for (int i = 0; i < chars.size(); ++i)
		{
			auto& c = chars[i];
			characters.insert(std::make_pair(
				c["id"].ToInt(),
				Font::Character
				{
					(uint32_t)c["id"].ToInt(),
					(float)c["x"].ToInt(),
					(float)c["y"].ToInt(),
					(float)c["width"].ToInt(),
					(float)c["height"].ToInt(),
					(float)c["xoffset"].ToInt(),
					(float)c["yoffset"].ToInt(),
					(float)c["xadvance"].ToInt(),
					(uint32_t)c["page"].ToInt(),
				}));
		}

		float lineHeight = (float)fontJson["common"]["lineHeight"].ToInt();

		return std::make_shared<Font>(lineHeight, pageTextures, characters);
	}

	Vector2f Util::ScreenSpaceToPixelPosition(const Vector2f& point, const Vector4i& viewport)
	{
		return Vector2f(
			viewport.x + ((point.x * 0.5f + 0.5f) * viewport.z),
			viewport.y + (viewport.w - ((point.y * 0.5f + 0.5f) * viewport.w)));
	}

	bool Util::WorldPointToNormalisedScreenPoint(const Vector3f& position, Vector2f& result, const Matrix4x4& projectionMatrix, const Matrix4x4& viewMatrix, float maxDistance, float& distance)
	{
		Vector4f in(position.x, position.y, position.z, 1.0f);
		in = projectionMatrix * (viewMatrix * in);

		distance = in.w;

		if (in.w < 0.001f || in.w > maxDistance)
		{
			return false;
		}

		in.w = 1.0f / in.w;
		in *= in.w;

		result = Vector2f(in.x, in.y);

		return true;
	}
}
