
#include <App/BedEngineApplication.h>

#include "Gameplay/TesterWorld.h"

// TODO: Make this able to be editied by the editor when creating project

class TesterGame : public Bed::Application
{
    
};


/*
    TODO: Make the game world load from an asset file JSON
    E.G

    GameWorld = "Assets/Worlds/TestWorld.world"

    TODO: Also make Application settings be able to be loaded by Json
    TODO: When game gets built anything that the developer doesnt want included in file structure like worlds or Incarns make them copy their contents into the engine for reading
*/

Bed::Application* CreateApplication()
{
    Bed::Application* App = new TesterGame;
    const char* Name = "Playground";
    App->SetApplicationName(Name);

    Test::TestWorld* gameWorld = new Test::TestWorld();

    App->SetGame(gameWorld);

    return App;
}