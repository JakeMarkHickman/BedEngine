
#include <BedEngineApplication.h>
#include <iostream>

#include "GameMap.h"

// TODO: Make this able to be editied by the editor when creating project

class TesterGame : public Bed::Application
{
    
};

Bed::Application* CreateApplication()
{
    Bed::Application* App = new TesterGame;
    const char* Name = "Playground";
    std::cout << "Creating GameMap" << std::endl;
    Bed::Map* map = new Game::GameMap();
    std::cout << "Created GameMap" << std::endl;
    App->SetApplicationName(Name);
    App->SetMap(map);

    return App;
}