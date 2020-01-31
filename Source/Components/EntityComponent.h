#pragma once

namespace Freeking
{
	class IEntityComponent
	{
	public:

		IEntityComponent() = default;
		virtual ~IEntityComponent() = default;

		virtual void Initialize() = 0;
		virtual void PostInitialize() = 0;
		virtual void Tick(double dt) = 0;
		virtual void PostTick() = 0;
	};
}
