
#include <App/BedEngineApplication.h>

#include "Gameplay/Game.h"

/*
    TODO: Make the game world load from an asset file JSON
    E.G

    GameWorld = "Assets/Worlds/TestWorld.world"

    TODO: Also make Application settings be able to be loaded by Json
    TODO: When game gets built anything that the developer doesnt want included in file structure like worlds or Incarns make them copy their contents into the engine for reading
*/

Bed::Application* CreateApplication()
{
    Bed::Application* App = new Bed::Application;
    const char* Name = "Playground";
    const char* Icon = "Assets/Resources/Textures/LittleGuy.png";
    Test::Game* game = new Test::Game();
    
    App->SetApplicationName(Name);
    App->SetWindowIcon(Icon);
    App->SetGame(game);

    return App;
}