#include "ModelEntity.h"
#include "DynamicModel.h"

namespace Freeking
{
	ModelEntity::ModelEntity() : PrimitiveEntity()
	{
	}

	void ModelEntity::Tick(double dt)
	{
		PrimitiveEntity::Tick(dt);
	}

	void ModelEntity::Initialize()
	{
		PrimitiveEntity::Initialize();
	}

	void ModelEntity::RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<Shader>& shader)
	{

	}

	void ModelEntity::RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<Shader>& shader)
	{

	}

	bool ModelEntity::SetProperty(const EntityProperty& property)
	{
		return PrimitiveEntity::SetProperty(property);
	}
}
