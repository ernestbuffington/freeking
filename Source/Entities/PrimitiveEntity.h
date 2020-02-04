#pragma once

#include "SceneEntity.h"

namespace Freeking
{
	class PrimitiveEntity : public SceneEntity
	{
	public:

		PrimitiveEntity();

		virtual void PreRender(bool translucent) = 0;
		virtual void RenderOpaque() = 0;
		virtual void RenderTranslucent() = 0;

	protected:

		Shader* _shader;
	};
}
