#pragma once

#include "BspStructures.h"
#include "Vector.h"
#include <stdint.h>

namespace Freeking
{
	template<typename ElementType>
	struct LumpArray
	{
	public:

		LumpArray() :
			DataPtr(nullptr),
			DataSize(0)
		{
		}

		LumpArray& operator=(const LumpArray& other)
		{
			DataPtr = other.DataPtr;
			DataSize = other.DataSize;

			return *this;
		}

		inline int Num() const { return DataSize; }
		inline const ElementType* Data() const { return DataPtr; }

		inline bool IsValidIndex(int Index) const { return Index >= 0 && Index < Num(); }

		const ElementType& operator[](int Index) const
		{
			return DataPtr[Index];
		}

	private:

		LumpArray(ElementType* InData, int InDataSize) :
			DataPtr(InData),
			DataSize(InDataSize)
		{
		}

		ElementType* DataPtr;
		int DataSize;

		friend struct BspFile;
	};

	struct BspFile
	{
		static const BspFile& Create(const uint8_t* Data)
		{
			return (const BspFile&)*Data;
		}

		inline bool IsValid() const
		{
			return Header.MagicNumber == MagicNumber && Header.Version == Version;
		}

		template<typename ElementType>
		LumpArray<ElementType> GetLumpArray(const BspLumpHeader& Lump) const
		{
			return LumpArray<ElementType>((ElementType*)((const char*)this + Lump.Offset), Lump.Length / sizeof(ElementType));
		}

		static const int MagicNumber = 0x50534249;
		static const int Version = 38;

		BspHeader Header;
	};
}
