#pragma once

#include <Graphics/Vertex.h>
#include <Bed/Tools/FileLoader.h>
#include <iostream>

namespace Bed
{
    class Mesh
    {
    public:
        Mesh(std::string path);
        
    private:
        std::string m_Data;
        uint64_t m_Count;
    };
}