#pragma once

#include <string>

namespace Bed
{
    enum class TextureFiltering
    {
        Nearest,
        Bilinear,
        Trilinear
    };

    class TextureAsset
    {
    public:
        TextureAsset(const std::string& path, TextureFiltering textureFiltering = TextureFiltering::Bilinear) : m_FilePath(path), m_TextureFiltering(textureFiltering) {};

        virtual void Bind(unsigned int slot = 0) const {};
        virtual void Unbind() const {};

        int GetWidth() { return m_Width; };
        int GetHeight() { return m_Height; };

    protected:
        int m_Width;
        int m_Height;
        TextureFiltering m_TextureFiltering;
        std::string m_FilePath;
        
    };
}