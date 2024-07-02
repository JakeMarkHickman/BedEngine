#pragma once

#include "..\Core.h"

namespace Bed
{
    
    class BED_API Application
    {
    public:
        void Run();
    }; 

    Application* CreateApplication();
    

} // namespace Bed
