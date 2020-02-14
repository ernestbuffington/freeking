#pragma once

#include "Matrix4x4.h"
#include <vector>

namespace Freeking
{
	class Shader;
	class VertexBinding;

	enum class DrawPrimitive
	{
		Triangles,
		Lines,
	};

	class Renderer
	{
	public:

		static Matrix4x4 ProjectionMatrix;
		static Matrix4x4 ViewMatrix;
		static float ViewportWidth;
		static float ViewportHeight;
		static bool DebugDraw;

		static void Draw(
			VertexBinding* binding,
			Shader* shader,
			DrawPrimitive primitive = DrawPrimitive::Triangles,
			int offset = 0,
			int count = 0,
			int instances = 0);
	};
}
