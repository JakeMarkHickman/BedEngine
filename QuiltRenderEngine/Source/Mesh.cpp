#include "Mesh.h"

unsigned int Quilt::MeshManager::CreateMeshHandle(const std::string& name, Quilt::Mesh& mesh)
{
    unsigned int handle = m_Meshes.size();

    m_Meshes.push_back(mesh);
    m_HandleCache.emplace(name, handle);

    return handle;
}

unsigned int Quilt::MeshManager::CreateMeshHandle(const std::string& path)
{
    unsigned int handle = m_Meshes.size();

    Quilt::OBJLoader loader(path);

    Quilt::Mesh newMesh;
    newMesh.Vertices = loader.GetVertices();
    newMesh.Indices = loader.GetIndices();

    m_Meshes.push_back(newMesh);
    m_HandleCache.emplace(path, handle);

    return handle;
}

bool Quilt::MeshManager::IsMeshCached(const std::string& key)
{
    return m_HandleCache.find(key) != m_HandleCache.end();
} 

unsigned int Quilt::MeshManager::GetMeshHandle(const std::string& key)
{
    return m_HandleCache.at(key);
}

Quilt::Mesh& Quilt::MeshManager::GetMeshData(const unsigned int& MeshHandle)
{
    return m_Meshes[MeshHandle];
}