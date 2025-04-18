#pragma once

#include <Graphics/Texture.h>

namespace Bed
{
    class OpenTexture : public Bed::Texture
    {
    public:
        OpenTexture(const std::string& path);
        ~OpenTexture();

        // change this to 

        virtual void Bind(unsigned int slot = 0) const override;
        virtual void Unbind() const override;
        
        int GetWidth() { return m_Width; };
        int GetHeight() { return m_Height; };
    private:

        unsigned int m_RendererID;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BitsPerPixel;
    };
}