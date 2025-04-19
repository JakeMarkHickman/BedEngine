#pragma once

#include <Graphics/TextureAsset.h>
#include <string>

namespace Bed
{
    struct Material
    {
        Material() : TexturePath("None") {};
        Material(std::string texturePath) : TexturePath(texturePath) {};

        std::string TexturePath;

        Bed::TextureAsset* Texture = nullptr;
        unsigned int TextureSlot = 1;
    };
}