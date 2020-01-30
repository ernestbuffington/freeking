#pragma once

#include "VertexBinding.h"
#include "VertexBuffer.h"
#include "Quaternion.h"
#include <vector>

namespace Freeking
{
	class Material;

	class LineRenderer
	{
	public:

		LineRenderer(std::size_t maxVertexCount);

		void DrawLine(const Vector3f& p1, const Vector3f& p2, const Vector4f& colour);
		void DrawAABBox(const Vector3f& mins, const Vector3f& maxs, const Vector4f& colour);
		void DrawAABBox(const Vector3f& position, const Vector3f& mins, const Vector3f& maxs, const Vector4f& colour);
		void DrawSphere(const Vector3f& position, float radius, int thetaSegments, int phiSegments, const Vector4f& colour);
		void DrawCone(const Vector3f& position, float radius, float height, std::size_t sides, const Vector4f& colour);
		void DrawCone(const Vector3f& position, const Quaternion& rotation, float radius, float height, std::size_t sides, const Vector4f& colour);

		void Flush(Matrix4x4& viewProj);

		inline std::size_t GetVertexCount() const { return _vertexCount; }
		inline std::size_t GetMaxVertexCount() const { return _maxVertexCount; }

	private:

		void BufferVertex(const Vector3f& position, const Vector4f& colour);

		static const std::size_t VertexSize = 28;
		std::size_t _vertexCount;
		std::size_t _maxVertexCount;

		std::unique_ptr<VertexBuffer> _vertexBuffer;
		std::unique_ptr<VertexBinding> _vertexBinding;
		std::vector<uint8_t> _buffer;
		std::shared_ptr<Material> _material;
	};
}
