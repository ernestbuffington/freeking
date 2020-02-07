#pragma once

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

		static void Draw(
			VertexBinding* binding,
			Shader* shader,
			DrawPrimitive primitive = DrawPrimitive::Triangles,
			int offset = 0,
			int count = 0,
			int instances = 0);
	};
}
