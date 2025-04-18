#pragma once

#include <Graphics/Texture.h>
#include <string>

namespace Bed
{
    struct Material
    {
        Material() : TexturePath("None") {};
        Material(std::string texturePath) : TexturePath(texturePath) {};

        std::string TexturePath;

        Bed::Texture* Texture = nullptr;
        unsigned int TextureSlot = 1;
    };
}