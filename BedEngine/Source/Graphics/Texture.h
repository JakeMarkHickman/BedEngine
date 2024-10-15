#pragma once

#include <string>

namespace Bed
{
    class Texture
    {
    public:
        Texture(const std::string& path);
        ~Texture();

        // change this to 

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;
        
        int GetWidth() { return m_Width; };
        int GetHeight() { return m_Height; };

    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BitsPerPixel;
    };
}