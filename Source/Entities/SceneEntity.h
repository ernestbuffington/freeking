#pragma once

#include "BaseEntity.h"

namespace Freeking
{
	class SceneEntity : public BaseEntity
	{
	public:

		SceneEntity();

		virtual void InitializeProperties(const EntityLump::EntityDef& def) override;
		virtual void Initialize() override;
		virtual void PostInitialize() override;
		virtual void Tick(double dt) override;
		virtual void PostTick() override;
		virtual void Spawn() override;

		inline void SetPosition(const Vector3f& position) { _position = position; }
		inline void SetRotation(const Quaternion& rotation) { _rotation = rotation; }
		inline void AddPosition(const Vector3f& position) { _position += position; }
		inline void AddRotation(const Quaternion& rotation) { _rotation *= rotation; }

		inline const Vector3f& GetPosition() const { return _position; }
		inline const Quaternion& GetRotation() const { return _rotation; }
		inline const Matrix4x4& GetTransform() const { return _transform; }

	protected:

		virtual bool SetProperty(const EntityKeyValue& keyValue) override;

	private:

		void UpdateTransform();

		Vector3f _position;
		Quaternion _rotation;
		Matrix4x4 _transform;
	};
}
