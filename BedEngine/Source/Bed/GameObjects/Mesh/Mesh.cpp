#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <string>
#include <Bed/Tools/StringSearcher.h>
#include <regex>

Bed::Mesh::Mesh(std::string path)
{
    std::string line;
    int faceCount = 0;

    std::ifstream file(path);
    // Loop through each line in the file
    while (std::getline(file, line)) {
        // Check if the line starts with "v "
        if (line.rfind("f ", 0) == 0) {
            ++faceCount;
        }
    }

    m_Faces.resize(faceCount);
}