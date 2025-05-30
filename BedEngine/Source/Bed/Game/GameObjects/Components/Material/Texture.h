#pragma once

#include <Graphics/TextureAsset.h>
#include <string>
#include <Math/Vector/Vector2.h>

namespace Bed
{
    //TODO: Diffrent texture modes such as nearest or linear ect
    struct Texture
    {
        Texture() : TexturePath("None") {};
        Texture(std::string texturePath, TextureFiltering textureFiltering = TextureFiltering::Bilinear, bool lockSlot = false) : TexturePath(texturePath), LockSlot(lockSlot), TextureFiltering(textureFiltering) {};

        std::string TexturePath;

        Pillow::Vector2f TextureSize;

        TextureFiltering TextureFiltering;
        Bed::TextureAsset* TextureAsset = nullptr;
        unsigned int TextureSlot = 0;
        bool LockSlot = false;
    };
}