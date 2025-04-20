#pragma once

#include <Graphics/TextureAsset.h>
#include <string>

namespace Bed
{
    struct Texture
    {
        Texture() : TexturePath("None") {};
        Texture(std::string texturePath, bool lockSlot = false) : TexturePath(texturePath), LockSlot(lockSlot) {};

        std::string TexturePath;

        Bed::TextureAsset* TextureAsset = nullptr;
        unsigned int TextureSlot = 0;
        bool LockSlot = false;
    };
}