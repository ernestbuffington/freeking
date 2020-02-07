#include "BrushModelEntity.h"
#include "Map.h"
#include "Util.h"
#include "LineRenderer.h"
#include "SpriteBatch.h"

namespace Freeking
{
	BrushModelEntity::BrushModelEntity() : PrimitiveEntity(),
		_modelIndex(-1)
	{
	}

	void BrushModelEntity::Tick(double dt)
	{
		PrimitiveEntity::Tick(dt);

		if (_model)
		{
			LineRenderer::Debug->DrawBox(GetTransform(), GetLocalMinBounds(), GetLocalMaxBounds(), LinearColor(0, 1, 0, 1));

			auto position = GetTransformCenter().Translation();

			Vector2f screenPosition;
			if (Util::WorldPointToNormalisedScreenPoint(position, screenPosition, SpriteBatch::ProjectionMatrix, SpriteBatch::ViewMatrix, 2048.0f))
			{
				float alpha = 0.75f;
				screenPosition = Util::ScreenSpaceToPixelPosition(screenPosition, Vector4i(0, 0, (int)SpriteBatch::ViewportWidth, (int)SpriteBatch::ViewportHeight));
				screenPosition.x = Math::Round(screenPosition.x);
				screenPosition.y = Math::Round(screenPosition.y);
				auto text = _classname + " (*" + std::to_string(_modelIndex) + ")";
				SpriteBatch::Debug->DrawText(nullptr, text, screenPosition + Vector2f(2, 2), LinearColor(0, 0, 0, alpha), 0.5f);
				SpriteBatch::Debug->DrawText(nullptr, text, screenPosition, LinearColor(0.5f, 1, 0.5f, alpha), 0.5f);
			}
		}
	}

	void BrushModelEntity::Initialize()
	{
		PrimitiveEntity::Initialize();

		if (_model = Map::Current->GetBrushModel(_modelIndex))
		{
			SetLocalBounds(_model->BoundsMin, _model->BoundsMax);
		}

		_shader = Shader::Library.Lightmapped.get();
	}

	void BrushModelEntity::PreRender(bool translucent)
	{
		if (_shader)
		{
			if (translucent)
			{
				_shader->SetParameterValue("alphaCutOff", 0.0f);
			}
			else
			{
				_shader->SetParameterValue("alphaMultiply", 1.0f);
			}

			_shader->SetParameterValue("model", GetTransform());
		}
	}

	void BrushModelEntity::RenderOpaque()
	{
		if (_model && _shader && !HasSurf2Alpha())
		{
			_model->RenderOpaque(_shader);
		}
	}

	void BrushModelEntity::RenderTranslucent()
	{
		if (_model && _shader)
		{
			_model->RenderTranslucent(_shader, HasSurf2Alpha());
		}
	}

	bool BrushModelEntity::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("model"))
		{
			return property.ValueAsModelIndex(_modelIndex);
		}

		return PrimitiveEntity::SetProperty(property);
	}

	void BrushModelEntity::Trace(const Vector3f& start, const Vector3f& end, TraceResult& trace, const BspContentFlags& brushMask)
	{
		if (_modelIndex == 0)
		{
			return;
		}

		trace = Map::Current->TransformedBoxTrace(start, end, 0, 0, Map::Current->GetModelHeadNode(_modelIndex), brushMask, GetPosition(), GetRotation());
	}
}
