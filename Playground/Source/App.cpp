
#include <BedEngineApplication.h>

#include "GameMap.h"

// TODO: Make this able to be editied by the editor when creating project

class TesterGame : public Bed::Application
{
    
};

Bed::Application* CreateApplication()
{
    Bed::Application* App = new TesterGame;
    const char* Name = "Playground";
    Bed::Map* map = new Game::GameMap();
    App->SetApplicationName(Name);
    App->SetMap(map);

    return App;
}