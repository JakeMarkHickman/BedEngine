#pragma once

#include <Vector/Vector2.h>
#include <Vector/Vector3.h>
#include <Vector/Vector4.h>
#include <Transform.h>

#include "Vertex.h"

#include <vector>
#include <string>

namespace Quilt
{
    class OBJLoader
    {
    public:
        OBJLoader(std::string path);

        std::vector<Quilt::Vertex> GetVertices() { return m_Vertices; };
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
        
        std::vector<Quilt::Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;
    };
}