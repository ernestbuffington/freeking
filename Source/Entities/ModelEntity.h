#pragma once

#include "PrimitiveEntity.h"

namespace Freeking
{
	class DynamicModel;
	class Texture2D;

	class ModelEntity : public PrimitiveEntity
	{
	public:

		ModelEntity();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;

		virtual void PreRender(bool translucent) override;
		virtual void RenderOpaque() override;
		virtual void RenderTranslucent() override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

		std::string _modelName;
		std::string _skinName;

	private:

		std::shared_ptr<DynamicModel> _model;
		std::shared_ptr<Texture2D> _texture;
	};
}
