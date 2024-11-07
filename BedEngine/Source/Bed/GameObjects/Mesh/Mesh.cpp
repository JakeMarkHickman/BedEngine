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
        GrabData(line);
    }

    m_Faces.resize(faceCount);
}

void GrabData(std::string line)
{
    if (line.rfind("v ", 0) == 0)
    {

    }
    else if (line.rfind("vt ", 0) == 0)
    {

    }
    else if (line.rfind("vn ", 0) == 0)
    {

    }
    else if (line.rfind("f ", 0) == 0)
    {
        
    }
}

void Bed::Mesh::LoadVertices(std::string line)
{
    
}

void Bed::Mesh::LoadUVWs(std::string line)
{
    
}

void Bed::Mesh::LoadVertexNormals(std::string line)
{
    
}

void Bed::Mesh::LoadFaces(std::string line)
{
    
}