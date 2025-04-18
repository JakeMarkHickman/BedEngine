#pragma once

#include <Graphics/Texture.h>
#include <Graphics/OpenGL/OpenTexture.h>

#include <unordered_map>
#include <string>

namespace Bed
{
    class TextureManager
    {
    public:
        static Bed::Texture* LoadTexture(std::string path)
        {
            if(m_TextureLookup.find(path) != m_TextureLookup.end())
            {
                return m_TextureLookup[path];
            }

            //TODO: change this based on renderer and selected texture storage (eg. bindless textures)
            Bed::Texture* texture = new OpenTexture(path);

            std::cout << "Register Texture\n";
            m_TextureLookup[path] = texture;
            return texture;
        }

    private:
        static inline std::unordered_map<std::string, Bed::Texture*> m_TextureLookup;
    };
}