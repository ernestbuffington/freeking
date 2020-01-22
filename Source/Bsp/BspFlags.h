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

	inline bool operator&(BspSurfaceFlags a, BspSurfaceFlags b)
	{
		return static_cast<int>(a) & static_cast<int>(b);
	}
}
