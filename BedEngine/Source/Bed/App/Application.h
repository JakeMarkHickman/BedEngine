#pragma once

#include "..\Core.h"

namespace Bed
{
    
    class BED_API Application
    {
    public:
        void Run();

    protected:
        // TODO: Add variables that are able to be modified to 
        const char* m_ApplicationName;

    private:
        void Update();

    }; 

    Application* CreateApplication();
    

} // namespace Bed
