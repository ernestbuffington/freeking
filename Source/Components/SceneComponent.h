#pragma once

#include "EntityComponent.h"
#include "Vector.h"
#include "Quaternion.h"
#include "Matrix4x4.h"

namespace Freeking
{
	class SceneComponent : public IEntityComponent
	{
	public:

		virtual void Initialize() override;
		virtual void PostInitialize() override;
		virtual void Tick(double dt) override;
		virtual void PostTick() override;

		inline void SetPosition(const Vector3f& position) { _position = position; }
		inline void SetRotation(const Quaternion& rotation) { _rotation = rotation; }
		inline void AddPosition(const Vector3f& position) { _position += position; }
		inline void AddRotation(const Quaternion& rotation) { _rotation *= rotation; }

		inline const Vector3f& GetPosition() const { return _position; }
		inline const Quaternion& GetRotation() const { return _rotation; }
		inline const Matrix4x4& GetTransform() const { return _transform; }

	private:

		void UpdateTransform();

		Vector3f _position;
		Quaternion _rotation;
		Matrix4x4 _transform;
	};
}
