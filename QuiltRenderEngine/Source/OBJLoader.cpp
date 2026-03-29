#include "OBJLoader.h"
#include <fstream>
#include <string>
#include <sstream>

Quilt::OBJLoader::OBJLoader(std::string path)
{
    LoadFile(path);
}

void Quilt::OBJLoader::LoadFile(std::string path)
{
    //TODO: This currently only uses OBJ files. this will soon need to be expaneded!
    //TODO: OBJ loading and other file extention loading methods will need to be abstracted

    std::string line;
    std::ifstream file(path);
    // Loop through each line in the file
    while (std::getline(file, line)) {
        if (line.rfind("v ", 0) == 0)
        {
            LoadPositions(line);
        }
        else if (line.rfind("vt ", 0) == 0)
        {
            LoadUVWs(line);
        }
        else if (line.rfind("vn ", 0) == 0)
        {
            LoadVertexNormals(line);
        }
        else if (line.rfind("f ", 0) == 0)
        {
            LoadFaces(line);
        }
    }
}

void Quilt::OBJLoader::LoadPositions(std::string line)
{
    std::istringstream data(line.substr(2)); // Skip the "v "
    Pillow::Vector3f position(0.0f, 0.0f, 0.0f);

    data >> position.x >> position.y >> position.z;
    m_Positions.push_back(position);
}

void Quilt::OBJLoader::LoadUVWs(std::string line)
{
    std::istringstream data(line.substr(3)); // Skip the "vt "
    Pillow::Vector2f UVW(0.0f, 0.0f);

    data >> UVW.x >> UVW.y;
    m_UVs.push_back(UVW);
}

void Quilt::OBJLoader::LoadVertexNormals(std::string line)
{
    std::istringstream data(line.substr(3)); // Skip the "vn "
    Pillow::Vector3f normal(0.0f, 0.0f, 0.0f);

    data >> normal.x >> normal.y >> normal.z;
    m_Normals.push_back(normal);
}

void Quilt::OBJLoader::LoadFaces(std::string line)
{
    std::istringstream data(line.substr(2)); // Skip the "f "

    int faceCount = 0;
    std::string vertexData;
    
    // Current face indices
    std::vector<unsigned int> faceIndices;

    while(data >> vertexData)
    {
        int vi = 0, ti = 0, ni = 0;

        sscanf_s(vertexData.c_str(), "%d/%d/%d", &vi, &ti, &ni);

        Quilt::Vertex vert;
        vert.Position = m_Positions[vi - 1];
        vert.Normal = m_Normals[ni - 1];
        vert.Colour = Pillow::Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
        vert.TextureCoordinates = (ti > 0) ? m_UVs[ti - 1] : Pillow::Vector2f(0.0f, 0.0f);
        vert.TextureID = 0.0f;

        // Find if vertex already exists
        auto it = std::find(m_Vertices.begin(), m_Vertices.end(), vert);

        if (it != m_Vertices.end()) {
            // Vertex found; add its index to faceIndices
            faceIndices.push_back(static_cast<unsigned int>(std::distance(m_Vertices.begin(), it)));
        } else {
            // Vertex not found; add to m_Vertices and update faceIndices
            unsigned int newIndex = static_cast<unsigned int>(m_Vertices.size());
            m_Vertices.push_back(vert);
            faceIndices.push_back(newIndex);
        }
    }
    
    // Process faceIndices as triangles or quads (same as before)
    if (faceIndices.size() == 3) {
        m_Indices.insert(m_Indices.end(), faceIndices.begin(), faceIndices.end());
    } else if (faceIndices.size() == 4) {
        m_Indices.push_back(faceIndices[0]);
        m_Indices.push_back(faceIndices[1]);
        m_Indices.push_back(faceIndices[2]);

        m_Indices.push_back(faceIndices[0]);
        m_Indices.push_back(faceIndices[2]);
        m_Indices.push_back(faceIndices[3]);
    }
}