#pragma once

#include "Vector.h"
#include <vector>
#include <memory>

namespace Freeking
{
	class BillboardBatch;
	class VertexBuffer;
	class IndexBuffer;
	class VertexBinding;
	class Texture2D;
	class Shader;

	struct BillboardInstance
	{
		Vector3f position;
		Vector2f size;
		Vector4f color;
	};

	class LightFlares
	{
	public:

		static BillboardBatch* Billboards;
	};

	class BillboardBatch
	{
	public:

		BillboardBatch();

		void Draw(double dt, const Vector3f& eyePosition, const Vector3f& eyeDirection);
		void AddInstance(const Vector3f& position);

	private:

		std::shared_ptr<VertexBuffer> _vertexBuffer;
		std::shared_ptr<IndexBuffer> _indexBuffer;
		std::shared_ptr<VertexBuffer> _instanceBuffer;
		std::shared_ptr<VertexBinding> _vertexBinding;
		std::shared_ptr<Shader> _shader;
		std::vector<BillboardInstance> _instances;
	};
}
