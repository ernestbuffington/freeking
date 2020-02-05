#include "ALightflare.h"
#include "BillboardBatch.h"

namespace Freeking::Entity
{
	ALightflare::ALightflare() : SceneEntity()
	{
	}

	void ALightflare::Spawn()
	{
		BaseEntity::Spawn();

		LightFlares::Billboards->AddInstance(GetPosition());
	}
}
