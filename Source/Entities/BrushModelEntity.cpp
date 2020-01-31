#include "BrushModelEntity.h"
#include "Map.h"
#include "Util.h"

namespace Freeking
{
	BrushModelEntity::BrushModelEntity() : BaseWorldEntity(),
		_modelIndex(-1)
	{
	}

	void BrushModelEntity::Tick(double dt)
	{
		BaseWorldEntity::Tick(dt);
	}

	void BrushModelEntity::Initialize()
	{
		if (_modelIndex < 0)
		{
			return;
		}

		_model = Map::Current->GetBrushModel(_modelIndex);
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

	bool BrushModelEntity::SetProperty(const EntityKeyValue& keyValue)
	{
		if (keyValue.Key == "model" &&
			!keyValue.Value.empty() &&
			keyValue.Value[0] == '*')
		{
			return Util::TryParseInt(keyValue.Value.substr(1), _modelIndex);
		}

		return false;
	}
}
