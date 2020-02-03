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
			LineRenderer::Debug->DrawBox(GetTransform(), GetLocalMinBounds(), GetLocalMaxBounds(), Vector4f(0, 1, 0, 1));

			auto position = GetTransform() * (GetLocalMinBounds() + ((GetLocalMaxBounds() - GetLocalMinBounds()) * 0.5f));

			Vector2f screenPosition;
			if (Util::WorldPointToNormalisedScreenPoint(position, screenPosition, SpriteBatch::ProjectionMatrix, SpriteBatch::ViewMatrix, 2048.0f))
			{
				float alpha = 0.75f;
				screenPosition = Util::ScreenSpaceToPixelPosition(screenPosition, Vector4i(0, 0, (int)SpriteBatch::ViewportWidth, (int)SpriteBatch::ViewportHeight));
				screenPosition.x = Math::Round(screenPosition.x);
				screenPosition.y = Math::Round(screenPosition.y);
				auto text = _classname + " (*" + std::to_string(_modelIndex) + ")";
				SpriteBatch::Debug->DrawText(nullptr, text, screenPosition + Vector2f(2, 2), Vector4f(0, 0, 0, alpha), 0.5f);
				SpriteBatch::Debug->DrawText(nullptr, text, screenPosition, Vector4f(0.5f, 1, 0.5f, alpha), 0.5f);
			}
		}
	}

	void BrushModelEntity::Initialize()
	{
		PrimitiveEntity::Initialize();

		if (_model = GetModel(); _model)
		{
			SetLocalBounds(_model->BoundsMin, _model->BoundsMax);
		}
	}

	void BrushModelEntity::RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material)
	{
		if (_model)
		{
			_model->RenderOpaque(viewProjection, material);
		}
	}

	void BrushModelEntity::RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material)
	{
		if (_model)
		{
			_model->RenderTranslucent(viewProjection, material);
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

	std::shared_ptr<BrushModel> BrushModelEntity::GetModel()
	{
		return _modelIndex < 0 ? nullptr : Map::Current->GetBrushModel(_modelIndex);
	}
}
