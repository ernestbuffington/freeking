#pragma once

#include "Md2Structures.h"
#include "DynamicModel.h"
#include <array>
#include <stdint.h>

namespace Freeking
{
	struct MD2File
	{
		static const MD2File& Create(const uint8_t* data)
		{
			return (const MD2File&)*data;
		}

		inline bool IsValid() const
		{
			return Header.Ident == Ident && Header.Version == Version;
		}

		template<typename T>
		const T* Read(uint32_t& offset, uint32_t count) const
		{
			auto ptr = (T*)((const char*)this + offset);
			offset += (sizeof(T) * count);

			return ptr;
		}

		static const int Ident = 0x32504449;
		static const int Version = 8;

		MD2Header Header;
	};
}
