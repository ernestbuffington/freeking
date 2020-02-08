#include "Util.h"
#include <charconv>
#include <random>

namespace Freeking
{
	float Util::RandomFloat(float a, float b)
	{
		static std::random_device rd;
		static std::mt19937 mt(rd());
		return std::uniform_real_distribution<float>(a, b)(mt);
	}

	Vector2f Util::ScreenSpaceToPixelPosition(const Vector2f& point, const Vector4i& viewport)
	{
		return Vector2f(
			viewport.x + ((point.x * 0.5f + 0.5f) * viewport.z),
			viewport.y + (viewport.w - ((point.y * 0.5f + 0.5f) * viewport.w)));
	}

	Vector2f Util::PixelPositionToScreenSpace(const Vector2f& point, const Vector4i& viewport)
	{
		return Vector2f(
			(((point.x - viewport.x) / viewport.z) - 0.5f) * 2.0f,
			(((point.y - viewport.y) / viewport.w) - 0.5f) * -2.0f);
	}

	bool Util::WorldPointToNormalisedScreenPoint(const Vector3f& position, Vector2f& result, const Matrix4x4& projectionMatrix, const Matrix4x4& viewMatrix, float maxDistance)
	{
		Vector4f in(position.x, position.y, position.z, 1.0f);
		in = projectionMatrix * (viewMatrix * in);

		if (in.w < 0.001f)
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

	bool Util::TryParseVector(const std::string& s, Vector3f& v)
	{
		auto xyz = SplitString(s, " ");
		if (xyz.size() != 3)
		{
			return false;
		}

		float x, y, z;
		if (!Util::TryParseFloat(xyz[0], x) ||
			!Util::TryParseFloat(xyz[1], y) ||
			!Util::TryParseFloat(xyz[2], z))
		{
			return false;
		}

		v = Vector3f(x, y, z);

		return true;
	}

	std::vector<std::string> Util::SplitString(const std::string& s, const std::string& delimiter)
	{
		std::vector<std::string> result;
		size_t start = 0;
		size_t end = 0;

		do
		{
			end = s.find(delimiter, start);
			size_t length = end - start;
			std::string token = s.substr(start, length);

			if (length > 0)
			{
				result.emplace_back(token);
			}

			start += length + delimiter.length();
		} while (end != std::string::npos);

		return result;
	}
}
