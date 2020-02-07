#pragma once

#include "SceneEntity.h"
#include "BspFlags.h"

namespace Freeking
{
	struct TraceResult
	{
		TraceResult() :
			hit(false),
			fraction(1.0f)
		{
		}

		bool allSolid;
		bool startSolid;
		float fraction;
		bool hit;
		Vector3f planeNormal;
		float planeDistance;
		Vector3f axisU;
		Vector3f axisV;
		Vector3f startPosition;
		Vector3f endPosition;
	};

	class PrimitiveEntity : public SceneEntity
	{
	public:

		PrimitiveEntity();

		virtual void Tick(double dt) override;

		virtual void PreRender(bool translucent) = 0;
		virtual void RenderOpaque() = 0;
		virtual void RenderTranslucent() = 0;

		virtual void Trace(const Vector3f& start, const Vector3f& end, TraceResult& trace, const BspContentFlags& brushMask);

	protected:

		Shader* _shader;
	};
}
