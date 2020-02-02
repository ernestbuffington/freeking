#pragma once

#include "MdxStructures.h"
#include "DynamicModel.h"
#include <array>
#include <stdint.h>

namespace Freeking
{
	struct MDXFile
	{
		static const MDXFile& Create(const char* data)
		{
			return (const MDXFile&)*data;
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

		static const int Ident = 0x58504449;
		static const int Version = 4;

		MDXHeader Header;
	};
}
