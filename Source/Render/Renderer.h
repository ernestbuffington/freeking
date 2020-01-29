#pragma once

#include <vector>

namespace Freeking
{
	class Material;
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
			Material* material,
			DrawPrimitive primitive = DrawPrimitive::Triangles,
			int offset = 0,
			int count = 0,
			int instances = 0);

		void Flush();

	private:

		struct DrawCall
		{
			VertexBinding* binding;
			Material* material;
			DrawPrimitive primitive;
			int offset;
			int count;
			int instances;
		};

		std::vector<DrawCall> _drawCalls;
	};
}
