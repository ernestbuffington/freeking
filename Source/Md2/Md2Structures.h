#pragma once

#include <array>
#include <stdint.h>

namespace Freeking
{
    struct MD2Header
    {
        int32_t Ident;
        int32_t Version;
        int32_t SkinWidth;
        int32_t SkinHeight;
        int32_t FrameSize;
        int32_t NumSkins;
        int32_t NumVertices;
        int32_t NumTexCoords;
        int32_t NumTriangles;
        int32_t NumCommands;
        int32_t NumFrames;
        int32_t OffsetSkins;
        int32_t OffsetTexCoords;
        int32_t OffsetTriangles;
        int32_t OffsetFrames;
        int32_t OffsetCommands;
        int32_t OffsetEnd;
    };

    struct MD2Vertex
    {
        uint8_t X, Y, Z;
        uint8_t NormalIndex;
    };

    struct MD2TexCoord
    {
        int16_t S, T;
    };

    struct MD2Triangle
    {
        std::array<uint16_t, 3> VertexIndices;
        std::array<uint16_t, 3> TexCoordIndices;
    };

    struct MD2Frame
    {
        std::array<float, 3> Scale;
        std::array<float, 3> Translate;
        std::array<char, 16> Name;
    };

    struct MD2Skin
    {
        std::array<char, 64> Path;
    };

    struct MD2CommandVertex
    {
        std::array<float, 2> TextureCoordinates;
        int VertexIndex;
    };

    struct MD2Command
    {
        int TrisTypeNum;
    };
}
