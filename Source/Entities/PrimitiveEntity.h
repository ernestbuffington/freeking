#pragma once

#include "SceneEntity.h"

namespace Freeking
{
	class PrimitiveEntity : public SceneEntity
	{
	public:

		virtual void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<class Shader>& shader) = 0;
		virtual void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<class Shader>& shader) = 0;
	};
}
