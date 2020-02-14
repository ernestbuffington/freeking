#include "PrimitiveEntity.h"
#include "LineRenderer.h"
#include "Renderer.h"

namespace Freeking
{
	PrimitiveEntity::PrimitiveEntity() : SceneEntity(),
		_shader(nullptr),
		_hidden(false),
		_collisionEnabled(false)
	{
	}

	void PrimitiveEntity::Tick(double dt)
	{
		SceneEntity::Tick(dt);
	}

	void PrimitiveEntity::PostTick()
	{
		SceneEntity::PostTick();

		if (!_hidden && Renderer::DebugDraw)
		{
			const auto& transformCenter = GetTransformCenter();
			const auto& viewMatrix = Renderer::ViewMatrix;
			float distance = transformCenter.Translation().LengthBetween(viewMatrix.InverseTranslation());

			if (distance < 512.0f)
			{
				float alpha = 1.0f - (distance / 512.0f);
				LineRenderer::Debug->DrawAxis(transformCenter, 20.0f, 3.0f, alpha);
			}
		}
	}

	void PrimitiveEntity::Trace(const Vector3f& start, const Vector3f& end, const Vector3f& mins, const Vector3f& maxs, TraceResult& trace, const BspContentFlags& brushMask)
	{
	}
}
