#pragma once

#include "Application.h"

#ifdef BED_WINDOWS_PLATFORM //Run this if compile platform is Windows

 extern Bed::Application* CreateApplication();

 int main(int argc, char** argv)
 {
      Bed::Application* app = CreateApplication();
      app->Run();
      delete app;
 }

#endif
