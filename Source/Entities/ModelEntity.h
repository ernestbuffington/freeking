#pragma once

#include "PrimitiveEntity.h"

namespace Freeking
{
	class DynamicModel;

	class ModelEntity : public PrimitiveEntity
	{
	public:

		ModelEntity();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

		virtual void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<Shader>& shader) override;
		virtual void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<Shader>& shader) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

	protected:

		std::shared_ptr<DynamicModel> _model;
	};
}
