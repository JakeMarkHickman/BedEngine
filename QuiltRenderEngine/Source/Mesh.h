#pragma once

#include <vector>

#include "Vertex.h"

namespace Quilt
{
    struct Mesh
    {
        unsigned int BatchIndex; // The batch that the mesh is in
        uint64_t LocalIndex; // The index within the batch
        uint64_t VertexOffset; // Where the vertices starts in the Vertex Buffer
        uint64_t IndexOffset; // Where the Indices start in the Index Buffer
        uint64_t VertexCount;
        uint64_t IndexCount;

        std::vector<Quilt::Vertex> Vertices;
        std::vector<unsigned int> Indices;
    };
}