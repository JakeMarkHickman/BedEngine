#pragma once

#include <filesystem>

namespace Bed
{
    class FileLoader
    {
    public:
        // Returns the contents of a file
        static std::string GetFileContents(const std::filesystem::path& path);
    };
}