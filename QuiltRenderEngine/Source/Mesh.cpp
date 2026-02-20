#include "Mesh.h"

unsigned int Quilt::MeshManager::CreateMeshHandle()
{
    uint32_t meshID;

    if(!m_RemovedMeshIDs.empty())
    {
        meshID = m_RemovedMeshIDs.back();
        m_RemovedMeshIDs.pop_back();

        LOG_INFO("Recycled Mesh: ", meshID);

        return meshID;
    }

    meshID = m_MeshCount;
    m_MeshCount++;

    LOG_INFO("Created Mesh: ", meshID);

    m_Meshes.BatchIDs.resize(m_MeshCount);
    m_Meshes.TransformOffset.resize(m_MeshCount);
    m_Meshes.VertexOffsets.resize(m_MeshCount);
    m_Meshes.IndexOffsets.resize(m_MeshCount);
    m_Meshes.VertexCounts.resize(m_MeshCount);
    m_Meshes.IndexCounts.resize(m_MeshCount);
    m_Meshes.Vertices.resize(m_MeshCount);
    m_Meshes.Indices.resize(m_MeshCount);

    return meshID;
}

void Quilt::MeshManager::RemoveMesh(unsigned int& meshID)
{
    LOG_INFO("Removed Mesh: ", meshID);

    m_RemovedMeshIDs.push_back(meshID);

    //TODO: clear data??
}

void Quilt::MeshManager::SetMeshBatchID(unsigned int& meshID, unsigned int batchID)
{
    m_Meshes.BatchIDs[meshID] = batchID;
}

void Quilt::MeshManager::SetMeshTransformOffset(unsigned int& meshID, uint64_t transformOffset)
{
    m_Meshes.TransformOffset[meshID] = transformOffset;
}

void Quilt::MeshManager::SetMeshVertexOffset(unsigned int& meshID, uint64_t vertexOffset)
{
    m_Meshes.VertexOffsets[meshID] = vertexOffset;
}

void Quilt::MeshManager::SetMeshIndicesOffset(unsigned int& meshID, uint64_t indexOffset)
{
    m_Meshes.IndexOffsets[meshID] = indexOffset;
}

void Quilt::MeshManager::SetMeshVertexCount(unsigned int& meshID, uint64_t vertexCount)
{
    m_Meshes.VertexCounts[meshID] = vertexCount;
}

void Quilt::MeshManager::SetMeshIndexCount(unsigned int& meshID, uint64_t indexCount)
{
    m_Meshes.IndexCounts[meshID] = indexCount;
}

void Quilt::MeshManager::SetMeshVertices(unsigned int& meshID, std::vector<Quilt::Vertex> vertices)
{
    m_Meshes.Vertices[meshID] = vertices;
}

void Quilt::MeshManager::SetMeshIndices(unsigned int& meshID, std::vector<unsigned int> indices)
{
    m_Meshes.Indices[meshID] = indices;
}