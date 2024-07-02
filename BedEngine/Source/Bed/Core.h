#pragma once

#ifdef BED_WINDOWS_PLATFORM
    #ifdef BED_BUILD_DLL
        #define BED_API __declspec(dllexport)
    #else
	    #define BED_API __declspec(dllimport)
    #endif
#else
    #error Bed Engine currently only supports windows!
#endif