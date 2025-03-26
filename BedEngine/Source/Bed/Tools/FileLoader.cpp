#include "FileLoader.h"

#include <fstream>
#include <string>

std::string Bed::FileLoader::GetFileContents(const std::filesystem::path& path)
{
    //std::cout << "Loading data from " << path << std::endl;

    std::string line;
    std::string data;

    std::ifstream file(path);
    if(file.is_open())
    {
        while(std::getline(file, line))
        {
            data += line + "\n";
        }
        file.close();
    }
    else
    {
        //std::cout << "Unable to open file" << std::endl;
    }

    //std::cout << data;

    return data;
}
