#pragma once

#ifdef BED_LINUX_PLATFORM

#elif BED_MAC_PLATFORM

#elif BED_WINDOWS_PLATFORM
    #include <Platforms/Windows/Win32.h>
#endif

namespace Bed
{
    class PlatformFactory
    {
    public:
        static Bed::Platform* CreatePlatform(Bed::EGraphicsAPIFlags pipeline)
        {
            #ifdef BED_LINUX_PLATFORM

            #elif BED_MAC_PLATFORM

            #elif BED_WINDOWS_PLATFORM
                return new Bed::Win32(pipeline);
            #endif

            return nullptr;
        }
    };
}