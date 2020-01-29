#pragma once

#include "Vector.h"
#include "Matrix4x4.h"
#include <vector>

namespace Freeking
{
	struct Util
	{
		static std::shared_ptr<class ShaderProgram> LoadShader(const std::string& source);
		static Vector2f ScreenSpaceToPixelPosition(const Vector2f& point, const Vector4i& viewport);
		static bool WorldPointToNormalisedScreenPoint(const Vector3f& position, Vector2f& result, const Matrix4x4& projectionMatrix, const Matrix4x4& viewMatrix, float maxDistance);
		static bool TryParseFloat(const std::string& s, float& v);
		static bool TryParseInt(const std::string& s, int& v);
	};
}
