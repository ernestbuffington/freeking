#include "BrushModelEntity.h"
#include "Map.h"
#include "Util.h"
#include "LineRenderer.h"
#include "SpriteBatch.h"
#include "Renderer.h"

namespace Freeking
{
	BrushTriggerEntity::BrushTriggerEntity() : BrushModelEntity()
	{
		_collisionEnabled = false;
	}

	BrushModelEntity::BrushModelEntity() : PrimitiveEntity(),
		_modelIndex(-1)
	{
		_collisionEnabled = true;
	}

	void BrushModelEntity::Tick(double dt)
	{
		PrimitiveEntity::Tick(dt);
	}

	void BrushModelEntity::PostTick()
	{
		PrimitiveEntity::PostTick();

		if (_model && !_hidden && Renderer::DebugDraw)
		{
			auto position = GetTransformCenter().Translation();

			const auto& viewMatrix = Renderer::ViewMatrix;
			float distance = position.LengthBetween(viewMatrix.InverseTranslation());

			if (distance < 512.0f)
			{
				float alpha = 1.0f - (distance / 512.0f);

				LineRenderer::Debug->DrawBox(GetTransform(), GetLocalMinBounds(), GetLocalMaxBounds(), LinearColor(0, 1, 0, alpha));

				Vector2f screenPosition;
				if (Util::WorldPointToNormalisedScreenPoint(position, screenPosition, Renderer::ProjectionMatrix, Renderer::ViewMatrix, 2048.0f))
				{
					screenPosition = Util::ScreenSpaceToPixelPosition(screenPosition, Vector4i(0, 0, (int)Renderer::ViewportWidth, (int)Renderer::ViewportHeight));
					screenPosition.x = Math::Round(screenPosition.x);
					screenPosition.y = Math::Round(screenPosition.y);
					auto text = _classname + " (*" + std::to_string(_modelIndex) + ")";
					SpriteBatch::Debug->DrawText(nullptr, text, screenPosition + Vector2f(2, 2), LinearColor(0, 0, 0, alpha), 0.5f);
					SpriteBatch::Debug->DrawText(nullptr, text, screenPosition, LinearColor(0.5f, 1, 0.5f, alpha), 0.5f);
				}
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
			_shader->Bind();

			if (translucent)
			{
				_shader->SetParameterValue("alphaCutOff", 0.0f);
			}
			else
			{
				_shader->SetParameterValue("alphaMultiply", 1.0f);
			}

			_shader->SetParameterValue("modelMatrix", GetTransform());
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

	void BrushModelEntity::Trace(const Vector3f& start, const Vector3f& end, const Vector3f& mins, const Vector3f& maxs, TraceResult& trace, const BspContentFlags& brushMask)
	{
		if (_modelIndex == 0 || _hidden)
		{
			return;
		}

		trace = Map::Current->TransformedBoxTrace(start, end, mins, maxs, Map::Current->GetModelHeadNode(_modelIndex), brushMask, GetPosition(), GetRotation());
	}
}
