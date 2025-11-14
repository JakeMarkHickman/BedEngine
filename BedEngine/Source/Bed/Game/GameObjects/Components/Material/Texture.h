#pragma once

#include <string>
#include <Vector/Vector2.h>

namespace Bed
{
    struct Texture
    {
        Texture() : TexturePath("None") {};
        Texture(std::string texturePath, bool lockSlot = false) : TexturePath(texturePath), LockSlot(lockSlot) {};

        std::string TexturePath;

        Pillow::Vector2f TextureSize;

        unsigned int Handle;
        bool LockSlot = false;
    };
}