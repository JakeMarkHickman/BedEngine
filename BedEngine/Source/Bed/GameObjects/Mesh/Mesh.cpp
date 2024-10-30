#include "Mesh.h"

#include <string>
#include <Bed/Tools/StringSearcher.h>

Bed::Mesh::Mesh(std::string path)
{
    m_Data = Bed::FileLoader::GetFileContents(path);

    std::string data[] = { "v", "vt", "vn", "f"};
    std::string disjunction = Bed::StringSearcher::Disjunction(data, std::size(data));

    std::cout << disjunction << std::endl;
}