#pragma once

#include <Bed/Core.h>
#include <Bed/GameObjects/Map.h>

namespace Bed
{
    
    class BED_API Application
    {
    public:
        void Run();

        void SetApplicationName(const char* Name)
        {
            if(Name != m_ApplicationName)
            {
                m_ApplicationName = Name;
            }
        };

        void SetMap(Bed::Map* map)
        {
            m_Map = map;
        }

        const char* GetApplicationName()
        {
            return m_ApplicationName;
        };

    protected:
        // TODO: Add variables that are able to be modified to 
        const char* m_ApplicationName = "Bed Engine";

        /*TODO: Game Hierarchy
            App
                Game Instance [Can be Edited] (handles loading of levels and data persistance)
                    Level [Can be Edited] (the game world, also uses level streaming)
                        Level Manager [Can be Edited] (controls spawning, Data loading, basic level stuff)
        */
        Bed::Map* m_Map;

    private:
        void Update();

    }; 

    Application* CreateApplication();
    

} // namespace Bed
