#pragma once

#include <GraphicsAPI.h>

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

void CreateWindow(int width, int height, char* title);
void UpdateWindow();
bool IsWindowOpen();
void CloseWindow();
