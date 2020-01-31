#pragma once

#include "BaseWorldEntity.h"

namespace Freeking
{
	class BrushModel;

	class BrushModelEntity : public BaseWorldEntity
	{
	public:

		BrushModelEntity();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

		virtual void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material) override;
		virtual void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material) override;

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

	protected:

		int _modelIndex;
		std::shared_ptr<BrushModel> _model;
	};
}
