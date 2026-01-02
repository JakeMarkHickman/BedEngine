#pragma once

#include <vector>

#include "Vertex.h"

namespace Quilt
{
    struct MeshStorage
    {
        std::vector<unsigned int> BatchIDs;
        std::vector<uint64_t> LocalIndices;

        std::vector<uint64_t> VertexOffsets;
        std::vector<uint64_t> IndexOffsets;
        std::vector<uint64_t> VertexCounts;
        std::vector<uint64_t> IndexCounts;
    };

    class MeshManager
    {
    public:
        unsigned int CreateMesh();
        void RemoveMesh(unsigned int meshID);
        
    private:
        
    };
}