#include "ShaderAsset.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Bed::ShaderProgramSource Bed::ShaderAsset::ParseShader()
{
    std::ifstream stream(m_FilePath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    std::unordered_set<std::string> filesIncluded;
    std::string directory = m_FilePath.substr(0, m_FilePath.find_last_of("/\\"));


    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else if (line.find("#include") != std::string::npos)
        {
            size_t firstQuote = line.find('\"');
            size_t lastQuote = line.find_last_of('\"');

            if (firstQuote != std::string::npos && lastQuote != std::string::npos && lastQuote > firstQuote)
                {
                    std::string includePath = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);
                    std::string fullPath = directory + "/" + includePath;

                    std::string includedSource = ImplmentIncludes(fullPath, filesIncluded);
                    ss[(int)type] << includedSource << '\n';
                }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

std::string Bed::ShaderAsset::ImplmentIncludes(std::string path, std::unordered_set<std::string> includes)
{
    if(includes.count(path))
        return "";
        
    includes.insert(path);

    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open shader include: " << path << '\n';
        return "";
    }

    std::string result;
    std::string line;
    std::string directory = path.substr(0, path.find_last_of("/\\"));

    while (getline(file, line))
    {
        if (line.find("#include") != std::string::npos)
        {
            size_t firstQuote = line.find('\"');
               size_t lastQuote = line.find_last_of('\"');
               if (firstQuote != std::string::npos && lastQuote != std::string::npos && lastQuote > firstQuote)
            {
                std::string includePath = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);
                std::string fullPath = directory + "/" + includePath;
                result += ImplmentIncludes(fullPath, includes); // recursive include
            }
        }
        else
        {
            result += line + '\n';
        }
    }

    return result;
}