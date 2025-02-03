#pragma once

#include <fstream>
#include <json.hpp>

namespace Bed
{
    class JsonRW
    {
    public:
        static nlohmann::json ReadFromFile(std::string path)
        {
            nlohmann::json jsonObj;

            std::ifstream inputFile(path);
            if(!inputFile.is_open())
            {
                std::cout << "File path: " << path << " could not be read" << "\n";
                return jsonObj;
            }

            try
            {
                inputFile >> jsonObj;
                inputFile.close();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            return jsonObj;
        }

        static void WriteToFile(std::string path)
        {

        }
    };

    
}