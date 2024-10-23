#pragma once

#include "Application.h"
#include <iostream>

extern Bed::Application* CreateApplication();

int main(int argc, char** argv)
{
     std::cout << "Creating app" << std::endl;
     Bed::Application* app = CreateApplication();
     std::cout << "Finished App" << std::endl;
     app->Run();
     delete app;
}
