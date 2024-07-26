#pragma once

#include "..\Core.h"

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

        const char* GetApplicationName()
        {
            return m_ApplicationName;
        };

    protected:
        // TODO: Add variables that are able to be modified to 
        const char* m_ApplicationName = "Bed Engine";

    private:
        void Update();

    }; 

    Application* CreateApplication();
    

} // namespace Bed
