#pragma once

#include "Mesh.h"
#include <Graphics/InstanceBuffer.h>

namespace Bed
{
    class InstancedMesh : public Bed::Mesh
    {
    public:
        InstancedMesh(std::string path)
        {
            LoadFile(path);
            
        }

        InstancedMesh(std::vector<Bed::Vertex> vertices, std::vector<unsigned int> indices)
        {
            
        }
    }
}