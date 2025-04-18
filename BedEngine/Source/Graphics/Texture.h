#pragma once

#include <string>

namespace Bed
{
    class Texture
    {
    public:
        Texture(const std::string& path) : m_FilePath(path) {};

        virtual void Bind(unsigned int slot = 0) const {};
        virtual void Unbind() const {};

    protected:
        
        std::string m_FilePath;
        
    };
}