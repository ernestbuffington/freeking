#include "Vector.h"
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
		uint32_t LightmapOffset;
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
		uint32_t Flags;
		uint32_t Value;
		char TextureName[32];
		uint32_t NextTextureInfo;
	};
}
