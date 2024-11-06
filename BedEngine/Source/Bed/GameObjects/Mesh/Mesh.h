#pragma once

#include <Graphics/Vertex.h>
#include <Bed/Tools/FileLoader.h>
#include <iostream>
#include <vector>

#include "MeshFace.h"

namespace Bed
{
    class Mesh
    {
    public:
        Mesh(std::string path);
        
    private:

        void LoadVertices();
        void LoadUVWs();
        void LoadVertexNormals();
        void LoadFaces();

        std::vector<Bed::MeshFace> m_Faces;
        
    };
}