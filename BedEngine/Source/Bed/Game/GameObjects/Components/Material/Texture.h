#pragma once

#include <string>
#include <Vector/Vector2.h>
#include <Duvet.h>

namespace Bed
{
    struct Texture
    {
        Texture() : TexturePath("None") {};
        Texture(std::string texturePath, bool lockSlot = false) : TexturePath(texturePath), LockSlot(lockSlot) {};

        std::string TexturePath;
        Quilt::TextureFiltering Filter = Quilt::TextureFiltering::Nearest;

        Pillow::Vector2f TextureSize;
        Pillow::Vector2f MinUV = Pillow::Vector2f(0.0f);
        Pillow::Vector2f MaxUV = Pillow::Vector2f(1.0f);

        unsigned int Handle;
        bool LockSlot = false;
    };
}