#include "Mesh.h"

#include <string>

Bed::Mesh::Mesh(std::string path)
{
    m_Data = Bed::FileLoader::GetFileContents(path);

    
}