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

		virtual void PreRender(bool translucent) override;
		virtual void RenderOpaque() override;
		virtual void RenderTranslucent() override;

		virtual void Trace(const Vector3f& start, const Vector3f& end, TraceResult& trace, const BspContentFlags& brushMask) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

		virtual bool HasSurf2Alpha() const { return false; }

	protected:

		int _modelIndex;
		std::shared_ptr<BrushModel> _model;
	};
}
