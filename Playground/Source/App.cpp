
#include <App/BedEngineApplication.h>

#include "Gameplay/Overworld.h"

// TODO: Make this able to be editied by the editor when creating project

class TesterGame : public Bed::Application
{
    
};

Bed::Application* CreateApplication()
{
    Bed::Application* App = new TesterGame;
    const char* Name = "Playground";
    App->SetApplicationName(Name);

    Game::Overworld* gameWorld = new Game::Overworld();

    App->SetGame(gameWorld);

    return App;
}