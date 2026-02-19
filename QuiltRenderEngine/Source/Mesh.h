#pragma once

#include <SleepTrace.h>
#include <vector>

#include "Vertex.h"

namespace Quilt
{
    struct MeshStorage
    {
        std::vector<unsigned int> BatchIDs;
        std::vector<uint64_t> TransformOffset;

        std::vector<uint64_t> VertexOffsets;
        std::vector<uint64_t> IndexOffsets;
        std::vector<uint64_t> VertexCounts;
        std::vector<uint64_t> IndexCounts;

        std::vector<std::vector<Quilt::Vertex>> Vertices;
        std::vector<std::vector<unsigned int>> Indices;
    };

    class MeshManager
    {
    public:
        /*
            Creates a Mesh Handle that will be used to access information about a mesh this includes:
                - The batch it is located in
                - Where the transform is located in the batch
                - Where the vertices are located in the batch
                - Where the Indices are located in the batch
                - Vertices Count
                - Indices Count
                - A copy of the Vertices uploaded
                - A copy of the Indices uploaded
        */
        unsigned int CreateMeshHandle();
        void RemoveMesh(unsigned int& meshID);

        void SetMeshBatchID(unsigned int& meshID, unsigned int batchID);
        void SetMeshTransformOffset(unsigned int& meshID, uint64_t transformOffset);
        void SetMeshVertexOffset(unsigned int& meshID, uint64_t vertexOffset);
        void SetMeshIndicesOffset(unsigned int& meshID, uint64_t indexOffset);
        void SetMeshVertexCount(unsigned int& meshID, uint64_t vertexCount);
        void SetMeshIndexCount(unsigned int& meshID, uint64_t indexCount);
        void SetMeshVertices(unsigned int& meshID, std::vector<Quilt::Vertex> vertices);
        void SetMeshIndices(unsigned int& meshID, std::vector<unsigned int> indices);


        unsigned int& GetMeshBatchID(unsigned int& meshID) { return m_Meshes.BatchIDs[meshID]; };
        uint64_t& GetMeshTransformOffset(unsigned int& meshID) { return m_Meshes.TransformOffset[meshID]; };
        uint64_t& GetMeshVertexOffset(unsigned int& meshID) { return m_Meshes.VertexOffsets[meshID]; };
        uint64_t& GetMeshIndicesOffset(unsigned int& meshID) { return m_Meshes.IndexOffsets[meshID]; };
        uint64_t& GetMeshVertexCount(unsigned int& meshID) { return m_Meshes.VertexCounts[meshID]; };
        uint64_t& GetMeshIndexCount(unsigned int& meshID) { return m_Meshes.IndexCounts[meshID]; };
        std::vector<Quilt::Vertex>& GetMeshVertices(unsigned int& meshID) { return m_Meshes.Vertices[meshID]; };
        std::vector<unsigned int>& GetMeshIndices(unsigned int& meshID) { return m_Meshes.Indices[meshID]; };

    private:
        //TODO: Reuse 

        //As meshes are just a handle to other data they will never be deleted
        Quilt::MeshStorage m_Meshes;
        uint32_t m_MeshCount = 0;
        std::vector<uint32_t> m_RemovedMeshIDs;
        
    };
}