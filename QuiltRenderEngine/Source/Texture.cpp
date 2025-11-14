#include "Texture.h"

#include <stb_image.h>
#include <unordered_map>

int Quilt::TextureManager::GetTextureSlots()
{
    if(m_MaxSlots <= -1)
    {
        AssignMaxSlots();
    }
            
    return m_MaxSlots;
}

int Quilt::TextureManager::AddTexture(const std::string& path, const TextureFiltering& filter)
{
    Quilt::Texture newTexture;

    int bitsPerPixel;

    stbi_set_flip_vertically_on_load(1);
    unsigned char* localBuffer = stbi_load(path.c_str(), &newTexture.Width, &newTexture.Hight, &bitsPerPixel, 4);

    GLCall(glGenTextures(1, &newTexture.Handle));
    GLCall(glBindTexture(GL_TEXTURE_2D, newTexture.Handle));

    int texturefilter;

    switch(filter)
    {
        case Quilt::TextureFiltering::Nearest:
            texturefilter = GL_NEAREST;
            break;
        case Quilt::TextureFiltering::Bilinear:
            texturefilter = GL_LINEAR;
            break;
        case Quilt::TextureFiltering::Trilinear:
            texturefilter = GL_LINEAR_MIPMAP_LINEAR;
            break;
    }

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texturefilter));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texturefilter));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, newTexture.Width, newTexture.Hight, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (localBuffer)
    {
        stbi_image_free(localBuffer);
    }

    newTexture.Slot = AssignSlot(path);

    m_Textures.emplace_back(newTexture);

    return newTexture.Slot;
}

int Quilt::TextureManager::AssignSlot(const std::string& path)
{
    //TODO: Make this more robust with a array to keep track of available texture slots
    if(IsTextureAssigned(path))
    {
        return m_SlotLookup[path];
    }

    if(IsAllSlotsFilled())
    {
        LOG_WARN("All slots are filled");
        return -1;
    }

    int slot = m_SlotLookup.size();
    m_SlotLookup[path] = slot;

    return slot;
}

bool Quilt::TextureManager::IsTextureAssigned(const std::string& path)
{
    return m_SlotLookup.find(path) != m_SlotLookup.end();
}

bool Quilt::TextureManager::IsAllSlotsFilled()
{
    return m_SlotLookup.size() >= m_MaxSlots;
}