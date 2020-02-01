#pragma once

#include "PrimitiveEntity.h"

namespace Freeking
{
	class BrushModel;

	class BrushModelEntity : public PrimitiveEntity
	{
	public:

		BrushModelEntity();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

		virtual void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material) override;
		virtual void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

		virtual std::shared_ptr<BrushModel> GetModel();

	protected:

		int _modelIndex;
		std::shared_ptr<BrushModel> _model;
	};
}
