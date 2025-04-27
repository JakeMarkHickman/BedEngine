#pragma once

#ifdef BED_LINUX_PLATFORM

#elif BED_MAC_PLATFORM

#elif BED_WINDOWS_PLATFORM
    #include <Platforms/Windows/GLFWWindow.h>
#endif

namespace Bed
{
    class WindowFactory
    {
    public:
        static Bed::Window* CreatePlatform(Bed::Platform* platform)
        {
            #ifdef BED_LINUX_PLATFORM

            #elif BED_MAC_PLATFORM

            #elif BED_WINDOWS_PLATFORM
                return new Bed::GLFWWindow(/*platform*/);
            #endif

            return nullptr;
        }
    };
}