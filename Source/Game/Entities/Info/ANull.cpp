#include "ANull.h"

namespace Freeking::Entity::Info
{
	ANull::ANull() : BaseEntity()
	{
	}

	void ANull::Initialize()
	{
	}

	void ANull::Tick(double dt)
	{
	}

	bool ANull::SetProperty(const EntityProperty& property)
	{
		return false;
	}
}
