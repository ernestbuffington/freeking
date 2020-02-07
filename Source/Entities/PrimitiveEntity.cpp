#include "PrimitiveEntity.h"
#include "LineRenderer.h"

namespace Freeking
{
	PrimitiveEntity::PrimitiveEntity() : SceneEntity(),
		_shader(nullptr)
	{
	}

	void PrimitiveEntity::Tick(double dt)
	{
		SceneEntity::Tick(dt);

		LineRenderer::Debug->DrawAxis(GetTransformCenter(), 20.0f, 3.0f);
	}

	void PrimitiveEntity::Trace(const Vector3f& start, const Vector3f& end, TraceResult& trace, const BspContentFlags& brushMask)
	{
	}
}
