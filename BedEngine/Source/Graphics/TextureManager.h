#pragma once

#include <Graphics/TextureAsset.h>
#include <Graphics/OpenGL/OpenTexture.h>

#include <unordered_map>
#include <string>

namespace Bed
{
    class TextureManager
    {
    public:
        static int AssignSlot(std::string path, bool lockSlot = false)
        {
            if(m_SlotLookup.find(path) != m_SlotLookup.end())
            {
                return m_SlotLookup[path];
            }

            int BoundNum = -1;
            
            //Assign and lock a number
            for(int i = 0; i < MAX_SLOTS; i++)
            {
                if(m_LockedSlots[i] != "") //Check if the slot is locked
                    continue;

                if(m_UsedSlots[i] == "")
                {
                    m_UsedSlots[i] = path;
                    m_SlotLookup[path] = i;
                    BoundNum = i;
                    break;
                }
            }

            return BoundNum;
        }

        static int GetSlot(std::string path)
        {
            if(m_SlotLookup.find(path) != m_SlotLookup.end())
            {
                return m_SlotLookup[path];
            }

            return 0;
        }

        static Bed::TextureAsset* LoadTexture(std::string path, TextureFiltering textureFiltering = TextureFiltering::Bilinear)
        {
            int Slot = AssignSlot(path);

            if(m_TextureLookup.find(Slot) != m_TextureLookup.end())
            {
                return m_TextureLookup[Slot];
            }

            //TODO: change this based on renderer and selected texture storage (eg. bindless textures)
            Bed::TextureAsset* texture = new OpenTexture(path, textureFiltering);
            m_TextureLookup[Slot] = texture;

            return texture;
        }

        static void UnbindTextures()
        {
            for(std::pair<const int, Bed::TextureAsset *> asset : m_TextureLookup)
            {
                asset.second->Unbind();
            }
        }

    private:
        static constexpr int MAX_SLOTS = 32; // number of bindable slots on the GPU

        static inline std::string m_UsedSlots[MAX_SLOTS];
        static inline std::string m_LockedSlots[MAX_SLOTS];
        
        static inline std::unordered_map<std::string, int> m_SlotLookup;
        static inline std::unordered_map<int, Bed::TextureAsset*> m_TextureLookup;
    };
}