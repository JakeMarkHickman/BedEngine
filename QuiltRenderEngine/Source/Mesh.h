#pragma once

#include <SleepTrace.h>
#include <vector>
#include <unordered_map>

#include "Vertex.h"
#include "OBJLoader.h"


namespace Quilt
{
    /*struct MeshStorage
    {
        std::vector<unsigned int> BatchIDs;
        std::vector<uint64_t> TransformOffset;

        std::vector<uint64_t> VertexOffsets;
        std::vector<uint64_t> IndexOffsets;
        std::vector<uint64_t> VertexCounts;
        std::vector<uint64_t> IndexCounts;

        std::vector<std::vector<Quilt::Vertex>> Vertices;
        std::vector<std::vector<unsigned int>> Indices;
    };*/

    struct Mesh
    {
        std::vector<Quilt::Vertex> Vertices;
        std::vector<unsigned int> Indices;
    };

    class MeshManager
    {
    public:
        unsigned int CreateMeshHandle(const std::string& name, Quilt::Mesh& mesh);
        unsigned int CreateMeshHandle(const std::string& path);

        bool IsMeshCached(const std::string& key);

        unsigned int GetMeshHandle(const std::string& key);
        Quilt::Mesh& GetMeshData(const unsigned int& MeshHandle);

    private:
        std::unordered_map<std::string, unsigned int> m_HandleCache;
        std::vector<Quilt::Mesh> m_Meshes;
    };
}