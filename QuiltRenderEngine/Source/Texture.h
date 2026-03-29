#pragma once

#include "OpenGl/OpenDebugger.h"

namespace Quilt
{
    enum class TextureFiltering
    {
        Nearest,
        Bilinear,
        Trilinear
    };

    struct Texture
    {
        unsigned int Handle;
        int Slot;

        int Hight;
        int Width;

        TextureFiltering Filter;
    };

    class TextureManager
    {
    public:
        int GetTextureSlots();
        std::vector<Quilt::Texture>& GetTextures() { return m_Textures; };
        int AddTexture(const std::string& path, const TextureFiltering& filter);
        bool IsTexture(unsigned int textureID);

    private:
    
        int AssignSlot(const std::string& path);
        bool IsTextureAssigned(const std::string& path);
        bool IsAllSlotsFilled();

        void AssignMaxSlots() 
        {
            GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_MaxSlots););
        }

        std::unordered_map<std::string, int> m_SlotLookup;
        std::vector<Texture> m_Textures;

        int m_MaxSlots = -1;
    };
}
