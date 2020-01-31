#include "SceneComponent.h"

namespace Freeking
{
	void SceneComponent::Initialize()
	{
	}

	void SceneComponent::PostInitialize()
	{
		UpdateTransform();
	}

	void SceneComponent::Tick(double dt)
	{
	}

	void SceneComponent::PostTick()
	{
		UpdateTransform();
	}

	void SceneComponent::UpdateTransform()
	{
		_transform = Matrix4x4::Translation(_position) * _rotation.ToMatrix4x4();
	}
}
