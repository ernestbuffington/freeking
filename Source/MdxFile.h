#pragma once

#include "MdxStructures.h"
#include "Mesh.h"
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
			return Header.Magic == MagicNumber && Header.Version == Version;
		}

		template<typename T>
		const T* Read(uint32_t& offset, uint32_t count) const
		{
			auto ptr = (T*)((const char*)this + offset);
			offset += (sizeof(T) * count);

			return ptr;
		}

		void Build(std::shared_ptr<KeyframeMesh>& mesh) const;

		static const int MagicNumber = 0x58504449;
		static const int Version = 4;

		MDXHeader Header;
	};
}
