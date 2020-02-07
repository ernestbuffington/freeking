#pragma once

#include "BspFlags.h"
#include "Vector.h"
#include "EnumFlags.h"
#include <array>
#include <stdint.h>

namespace Freeking
{
	struct BspLumpHeader
	{
		int32_t Offset;
		int32_t Length;
	};

	struct BspHeader
	{
		int32_t MagicNumber;
		int32_t Version;

		union
		{
			struct
			{
				BspLumpHeader Entities;
				BspLumpHeader Planes;
				BspLumpHeader Vertices;
				BspLumpHeader Visibility;
				BspLumpHeader Nodes;
				BspLumpHeader TextureInfo;
				BspLumpHeader Faces;
				BspLumpHeader Lightmaps;
				BspLumpHeader Leafs;
				BspLumpHeader LeafFaces;
				BspLumpHeader LeafBrushes;
				BspLumpHeader Edges;
				BspLumpHeader FaceEdges;
				BspLumpHeader Models;
				BspLumpHeader Brushes;
				BspLumpHeader BrushSides;
				BspLumpHeader Pop;
				BspLumpHeader Areas;
				BspLumpHeader AreaPortals;
			};

			BspLumpHeader LumpsHeaders[19];
		};
	};

	struct BspModel
	{
		Vector3f BoundsMin;
		Vector3f BoundsMax;
		Vector3f Origin;
		int32_t RootNode;
		int32_t FirstFace;
		int32_t NumFaces;
	};

	struct BspFace
	{
		uint16_t Plane;
		uint16_t PlaneSide;
		uint32_t FirstEdge;
		uint16_t NumEdges;
		uint16_t TextureInfo;
		uint8_t LightmapStyles[4];
		int32_t LightmapOffset;
	};

	struct BspEdge
	{
		int16_t A;
		int16_t B;
	};

	struct BspPlane
	{
		Vector3f Normal;
		float Distance;
		uint32_t Type;
	};

	struct BspTextureInfo
	{
		Vector3f AxisU;
		float OffsetU;
		Vector3f AxisV;
		float OffsetV;
		EnumFlags<BspSurfaceFlags> Flags;
		uint32_t Value;
		char TextureName[32];
		uint32_t NextTextureInfo;
	};

	struct BspBrushSide
	{
		uint16_t PlaneNum;
		int16_t TexInfo;
	};

	struct BspBrush
	{
		int32_t FirstSide;
		int32_t NumSides;
		EnumFlags<BspContentFlags> Contents;
	};

	struct BspLeaf
	{
		EnumFlags<BspContentFlags> Contents;
		int16_t Cluster;
		int16_t Area;
		std::array<int16_t, 3> Mins;
		std::array<int16_t, 3> Maxs;
		uint16_t FirstLeafFace;
		uint16_t NumLeafFaces;
		uint16_t FirstLeafBrush;
		uint16_t NumLeafBrushes;
	};

	struct BspNode
	{
		int32_t PlaneNum;
		std::array<int32_t, 2> Children;
		std::array<int16_t, 3> Mins;
		std::array<int16_t, 3> Maxs;
		uint16_t FirstFace;
		uint16_t NumFaces;
	};
}
