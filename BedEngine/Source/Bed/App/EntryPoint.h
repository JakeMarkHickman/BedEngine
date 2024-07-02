#pragma once

#include "Application.h"

#ifdef BED_WINDOWS_PLATFORM
 
 extern Bed::Application* CreateApplication();

 int main(int argc, char** argv)
 {
    Bed::Application* app = new Bed::Application();
    app->Run();
    delete app;
 }

#endif
