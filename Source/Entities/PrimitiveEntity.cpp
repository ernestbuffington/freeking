#include "PrimitiveEntity.h"
#include "LineRenderer.h"

namespace Freeking
{
	PrimitiveEntity::PrimitiveEntity() : SceneEntity(),
		_shader(nullptr),
		_hidden(false)
	{
	}

	void PrimitiveEntity::Tick(double dt)
	{
		SceneEntity::Tick(dt);

		if (!_hidden)
		{
			LineRenderer::Debug->DrawAxis(GetTransformCenter(), 20.0f, 3.0f);
		}
	}

	void PrimitiveEntity::Trace(const Vector3f& start, const Vector3f& end, TraceResult& trace, const BspContentFlags& brushMask)
	{
	}
}
