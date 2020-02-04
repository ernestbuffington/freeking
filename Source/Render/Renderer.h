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

		void Draw(
			VertexBinding* binding,
			Shader* shader,
			DrawPrimitive primitive = DrawPrimitive::Triangles,
			int offset = 0,
			int count = 0,
			int instances = 0);

		void Flush();

	private:

		struct DrawCall
		{
			VertexBinding* binding;
			Shader* shader;
			DrawPrimitive primitive;
			int offset;
			int count;
			int instances;
		};

		std::vector<DrawCall> _drawCalls;
	};
}
