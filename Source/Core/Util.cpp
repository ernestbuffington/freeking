#include "Util.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "FileSystem.h"
#include <charconv>
#include <filesystem>
#include <fstream> 

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
