#pragma once

#ifdef BED_LINUX_PLATFORM // Checks if the platform is Linux
    #include "Linux.cpp"
#elif BED_MAC_PLATFORM // Checks if the platform is Mac
    #include "Mac.cpp"
#elif BED_WINDOWS_PLATFORM // Checks if the platform is Windows
    #include "Windows.cpp"
#endif

//////////////////////////////////////////////////////////////////
//                         Functions                            //
//////////////////////////////////////////////////////////////////

bool PlatformCreateWindow(int width, int height, char* title);
void PlatformUpdateWindow();