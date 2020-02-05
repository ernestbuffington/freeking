#include "BillboardBatch.h"
#include "IndexBuffer.h"
#include "VertexBinding.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Map.h"
#include <array>

namespace Freeking
{
	BillboardBatch* LightFlares::Billboards = nullptr;

	static const std::array<Vector2f, 4> quadVertices =
	{
		Vector2f(-0.5, -0.5),
		Vector2f(0.5, -0.5),
		Vector2f(0.5, 0.5),
		Vector2f(-0.5, 0.5)
	};

	static const std::array<uint32_t, 6> quadIndices = { 0, 1, 2, 2, 3, 0 };

	BillboardBatch::BillboardBatch()
	{
		static const size_t vertStride = sizeof(Vector2f);
		static const size_t instanceStride = sizeof(BillboardInstance);

		_vertexBuffer = std::make_shared<VertexBuffer>(quadVertices.data(), quadVertices.size(), vertStride);
		_indexBuffer = std::make_shared<IndexBuffer>(quadIndices.data(), quadIndices.size(), GL_UNSIGNED_INT);
		_instanceBuffer = std::make_shared<VertexBuffer>(_instances.data(), 1000, instanceStride);

		ArrayElement vertexLayout[] = {
			ArrayElement(_vertexBuffer.get(), 0, 2, ElementType::Float, vertStride, 0),
			ArrayElement(_instanceBuffer.get(), 1, 3, ElementType::Float, instanceStride, 0 * sizeof(float), 1),
			ArrayElement(_instanceBuffer.get(), 2, 2, ElementType::Float, instanceStride, 3 * sizeof(float), 1),
			ArrayElement(_instanceBuffer.get(), 3, 4, ElementType::Float, instanceStride, 5 * sizeof(float), 1),
		};

		_vertexBinding = std::make_shared<VertexBinding>();
		_vertexBinding->Create(vertexLayout, 4, *_indexBuffer, ElementType::UInt);

		_shader = Shader::Library.Billboard;
		_shader->SetParameterValue("diffuse", Texture2D::Library.Get("sprites/corona_a.tga").get());
		_shader->SetParameterValue("brightness", 1.0f);
	}

	void BillboardBatch::Draw()
	{
		_shader->Apply();

		glBlendFunc(GL_ONE, GL_ONE);
		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);

		_vertexBinding->Bind();
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, _instances.size());
		_vertexBinding->Unbind();

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		_shader->Unbind();
	}

	void BillboardBatch::AddInstance(const Vector3f& position)
	{
		static const size_t instanceStride = sizeof(BillboardInstance);

		_instances.push_back({ position, Vector2f(200, 200), Vector4f(1, 1, 1, 1) });
		_instanceBuffer->UpdateBuffer(&_instances[_instances.size() - 1], (_instances.size() - 1) * instanceStride, instanceStride);
	}
}
