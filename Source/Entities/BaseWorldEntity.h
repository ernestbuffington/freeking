#pragma once

#include "BaseEntity.h"

namespace Freeking
{
	class Material;

	class BaseWorldEntity : public BaseEntity
	{
	public:

		BaseWorldEntity();

		virtual void InitializeProperties(const EntityLump::EntityDef& def) override;
		virtual void Initialize() override;
		virtual void PostInitialize() override;
		virtual void Tick(double dt) override;
		virtual void PostTick() override;
		virtual void Spawn() override;

		virtual void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material) = 0;
		virtual void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material) = 0;

		inline void SetPosition(const Vector3f& position) { _position = position; }
		inline void SetRotation(const Quaternion& rotation) { _rotation = rotation; }
		inline void AddPosition(const Vector3f& position) { _position += position; }
		inline void AddRotation(const Quaternion& rotation) { _rotation *= rotation; }

		inline const Vector3f& GetPosition() const { return _position; }
		inline const Quaternion& GetRotation() const { return _rotation; }
		inline const Matrix4x4& GetTransform() const { return _transform; }

	protected:

		void UpdateTransform();

		Vector3f _position;
		Quaternion _rotation;
		Matrix4x4 _transform;
	};
}
