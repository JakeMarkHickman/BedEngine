#pragma once

#include <Graphics/TextureAsset.h>

namespace Bed
{
    class OpenTexture : public Bed::TextureAsset
    {
    public:
        OpenTexture(const std::string& path, TextureFiltering textureFiltering);
        ~OpenTexture();

        virtual void Bind(unsigned int slot = 0) const override;
        virtual void Unbind() const override;
    private:

        unsigned int m_RendererID;
        unsigned char* m_LocalBuffer;
        int m_BitsPerPixel;
    };
}