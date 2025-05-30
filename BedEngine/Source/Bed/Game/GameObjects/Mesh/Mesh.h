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
        void LoadFile(std::string path);
        void LoadPositions(std::string line);
        void LoadUVWs(std::string line);
        void LoadVertexNormals(std::string line);
        void LoadFaces(std::string line);

        std::vector<Pillow::Vector3f> m_Positions;
        std::vector<Pillow::Vector2f> m_UVs;
        std::vector<Pillow::Vector3f> m_Normals;
        
        std::vector<Bed::Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;
    };
}