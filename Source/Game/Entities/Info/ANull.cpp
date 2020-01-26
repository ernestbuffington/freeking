#include "ANull.h"

namespace Freeking::Entity::Info
{
	ANull::ANull() : IEntity()
	{
	}

	void ANull::Initialize()
	{
	}

	void ANull::Tick(double dt)
	{
	}

	bool ANull::SetProperty(const EntityKeyValue& keyValue)
	{
		return false;
	}
}
