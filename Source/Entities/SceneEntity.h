#pragma once

#include "BaseEntity.h"

namespace Freeking
{
	class SceneEntity : public BaseEntity
	{
	public:

		SceneEntity();

		virtual void InitializeProperties(const EntityProperties& properties) override;
		virtual void Initialize() override;
		virtual void PostInitialize() override;
		virtual void Tick(double dt) override;
		virtual void PostTick() override;
		virtual void Spawn() override;

		inline const Vector3f& GetPosition() const { return _position; }
		inline const Quaternion& GetRotation() const { return _rotation; }
		inline const Matrix4x4& GetTransform() const { return _transform; }

		inline const Vector3f& GetLocalMinBounds() const { return _localMinBounds; }
		inline const Vector3f& GetLocalMaxBounds() const { return _localMaxBounds; }

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

		virtual void InitializeOriginProperty(const Vector3f& origin);
		virtual void InitializeAngleProperty(float angle);

		inline void SetPosition(const Vector3f& position) { _position = position; }
		inline void SetRotation(const Quaternion& rotation) { _rotation = rotation; }
		inline void AddPosition(const Vector3f& position) { _position += position; }
		inline void AddRotation(const Quaternion& rotation) { _rotation *= rotation; }

		void SetLocalBounds(const Vector3f& minBounds, const Vector3f& maxBounds);

	private:

		void UpdateTransform();

		Vector3f _position;
		Quaternion _rotation;
		Matrix4x4 _transform;

		Vector3f _localMinBounds;
		Vector3f _localMaxBounds;
	};
}
