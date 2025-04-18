#pragma once

#include <Graphics/Vertex.h>
#include <Bed/Tools/FileLoader.h>
#include <Math/Vector.h>
#include <Math/Transform.h>

#include <vector>

namespace Bed
{
    class Mesh
    {
    public:
        Mesh(std::string path);

        std::vector<Bed::Vertex> GetVertices() { return m_Vertices; };
        std::vector<unsigned int> GetIndices() { return m_Indices; };
        
    private:
        void LoadPositions(std::string line);
        void LoadUVWs(std::string line);
        void LoadVertexNormals(std::string line);
        void LoadFaces(std::string line);

        std::vector<Bed::Vector3> m_Positions;
        std::vector<Bed::Vector2> m_UVs;
        std::vector<Bed::Vector3> m_Normals;
        
        std::vector<Bed::Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;
    };
}