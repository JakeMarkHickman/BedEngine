#pragma once

#include "Platform.h"

#ifdef BED_LINUX_PLATFORM // Checks if the platform is Linux
    Bed::PlatformTypes PlatTypes = Bed::PlatformTypes::Linux;
    //#include "Linux.cpp"
#elif BED_MAC_PLATFORM // Checks if the platform is Mac
    Bed::PlatformTypes PlatTypes = Bed::PlatformTypes::Mac;
    //#include "Mac.cpp"
#elif BED_WINDOWS_PLATFORM // Checks if the platform is Windows
    Bed::PlatformTypes PlatTypes = Bed::PlatformTypes::Windows;
    #include "Win32.h"
#endif

Bed::Platform* Platform;

//////////////////////////////////////////////////////////////////
//                         Functions                            //
//////////////////////////////////////////////////////////////////

bool CreateWindow(int width, int height, const char* title, GraphicsAPI::EGraphicsAPIFlags Pipeline)
{

    switch (PlatTypes)
    {
    case Bed::PlatformTypes::Linux:
        break;
    
    case Bed::PlatformTypes::Mac:
        break;

    case Bed::PlatformTypes::Windows:
        Platform = new Bed::Win32();
        break;
    
    default:
        Platform = new Bed::Platform();
        break;
    }

    return Platform->PlatformCreateWindow(width, height, title, Pipeline);
}

void UpdateWindow()
{
    Platform->PlatformUpdateWindow();
}

bool IsWindowOpen()
{
    return Platform->PlatformIsWindowOpen();
}

void CloseWindow()
{
    Platform->PlatformCloseWindow();
    delete Platform;
}

