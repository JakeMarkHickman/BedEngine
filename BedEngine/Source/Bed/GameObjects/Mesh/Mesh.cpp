#include "Mesh.h"

#include <string>
#include <Bed/Tools/StringSearcher.h>

Bed::Mesh::Mesh(std::string path)
{
    m_Data = Bed::FileLoader::GetFileContents(path);

    std::string value[3] = { "Hello", "Earth", "Death"};
    Bed::StringSearcher::LookForString(value);
}