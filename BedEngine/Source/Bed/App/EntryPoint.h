#pragma once

#include "Application.h"

extern Bed::Application* CreateApplication();

 int main(int argc, char** argv)
 {
      Bed::Application* app = CreateApplication();
      app->Run();
      delete app;
 }
