#pragma once

#include <array>
#include <stdint.h>

namespace Freeking
{
	struct MDXHeader
	{
		int Ident;
		int Version;
		int SkinWidth;
		int SkinHeight;
		int FrameSize;
		int NumSkins;
		int NumVertices;
		int NumTriangles;
		int NumCommands;
		int NumFrames;
		int NumSfxDefines;
		int NumSfxEntries;
		int NumSubObjects;
		int OffsetSkins;
		int OffsetTriangles;
		int OffsetFrames;
		int OffsetCommands;
		int OffsetVertexInfo;
		int OffsetSfxDefines;
		int OffsetSfxEntries;
		int OffsetBBoxFrames;
		int OffsetDummyEnd;
		int OffsetEnd;
	};

	struct MDXVertex
	{
		std::array<uint8_t, 3> Vertex;
		uint8_t NormalIndex;
	};

	struct MDXTriangle
	{
		std::array<uint16_t, 3> VertexIndices;
		std::array<uint16_t, 3> TextureIndices;
	};

	struct MDXFrame
	{
		std::array<float, 3> Scale;
		std::array<float, 3> Translate;
		std::array<uint8_t, 16> Name;
	};

	struct MDXSkin
	{
		std::array<uint8_t, 64> Path;
	};

	struct MDXCommandVertex
	{
		std::array<float, 2> TextureCoordinates;
		int VertexIndex;
	};

	struct MDXCommand
	{
		int TrisTypeNum;
		int SubObjectID;
	};

	struct MDXBBox
	{
		float MinX;
		float MinY;
		float MinZ;
		float MaxX;
		float MaxY;
		float MaxZ;
	};
}
