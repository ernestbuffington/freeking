#pragma once

#include <stdint.h>

namespace Freeking
{
	enum class BspSurfaceFlags : uint32_t
	{
		Light = 0x1,
		Slick = 0x2,
		Sky = 0x4,
		Warp = 0x8,
		Trans33 = 0x10,
		Trans66 = 0x20,
		Flowing = 0x40,
		NoDraw = 0x80,
		Hint = 0x100,
		Skip = 0x200,
		Specular = 0x400,
		Diffuse = 0x800,
		Masked = 0x1000,
		Mirror = 0x2000,
		Window33 = 0x4000,
		Window66 = 0x8000,
		_10000 = 0x10000,
		_20000 = 0x20000,
		_40000 = 0x40000,
		Water = 0x80000,
		Concrete = 0x100000,
		Fabric = 0x200000,
		Gravel = 0x400000,
		Metal = 0x800000,
		MetalLite = 0x1000000,
		Tin = 0x2000000,
		Wood = 0x4000000,
		ReflectFake = 0x8000000,
		ReflectLight = 0x10000000,
		_20000000 = 0x20000000,
		_40000000 = 0x40000000,
		_80000000 = 0x80000000,
	};

	enum class BspContentFlags : uint32_t
	{
		Solid = 1,
		Window = 2,
		Aux = 4,
		Lava = 8,
		Slime = 16,
		Water = 32,
		Mist = 64,
		LastVisibleContents = 64,
		AreaPortal = 0x8000,
		PlayerClip = 0x10000,
		MonsterClip = 0x20000,
		Current0 = 0x40000,
		Current90 = 0x80000,
		Current180 = 0x100000,
		Current270 = 0x200000,
		CurrentUp = 0x400000,
		CurrentDown = 0x800000,
		Origin = 0x1000000,
		Monster = 0x2000000,
		DeadMonster = 0x4000000,
		Detail = 0x8000000,
		Translucent = 0x10000000,
		Ladder = 0x20000000,

		MaskAll = (uint32_t)(-1),
		MaskSolid = (Solid | Window),
		MaskPlayerSolid = (Solid | PlayerClip | Window | Monster),
		MaskDeadSolid = (Solid | PlayerClip | Window),
		MaskMonsterSolid = (Solid | MonsterClip | Window | Monster),
		MaskWater = (Water | Lava | Slime),
		MaskOpaque = (Solid | Slime | Lava),
		MaskSho = (Solid | Monster | Window | DeadMonster),
		MaskCurrent = (Current0 | Current90 | Current180 | Current270 | CurrentUp | CurrentDown)
	};
}
