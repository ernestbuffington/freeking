#pragma once

#include "SceneEntity.h"

namespace Freeking
{
	class PrimitiveEntity : public SceneEntity
	{
	public:

		virtual void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<class Material>& material) = 0;
		virtual void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<class Material>& material) = 0;
		virtual void RenderDebug(class LineRenderer* lineRenderer) = 0;
	};
}
