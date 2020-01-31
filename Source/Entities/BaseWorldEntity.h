#pragma once

#include "BaseEntity.h"
#include "SceneComponent.h"

namespace Freeking
{
	class Material;

	class BaseWorldEntity : public BaseEntity
	{
	public:

		BaseWorldEntity();

		virtual void InitializeProperties(const EntityLump::EntityDef& def) override;
		virtual void Initialize() override;
		virtual void Tick(double dt) override;

		virtual void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material) = 0;
		virtual void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material) = 0;

		inline void SetPosition(const Vector3f& position) { _rootComponent->SetPosition(position); }
		inline void SetRotation(const Quaternion& rotation) { _rootComponent->SetRotation(rotation); }
		inline void AddPosition(const Vector3f& position) { _rootComponent->AddPosition(position); }
		inline void AddRotation(const Quaternion& rotation) { _rootComponent->AddRotation(rotation); }

		inline const Vector3f& GetPosition() const { return _rootComponent->GetPosition(); }
		inline const Quaternion& GetRotation() const { return _rootComponent->GetRotation(); }
		inline const Matrix4x4& GetTransform() const { return _rootComponent->GetTransform(); }

	protected:

		SceneComponent* _rootComponent;
	};
}
