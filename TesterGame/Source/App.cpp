
#include <BedEngineApplication.h>

// TODO: Make this take place within the Engine DLL

class TesterGame : public Bed::Application
{

};

Bed::Application* CreateApplication()
{
    return new TesterGame;
}


/*int main()
{
    while(true)
    {
        //Update Loop
        Bed::Application* game = new Bed::Application();
        game->Run();
        delete game;
    }

    return 0;
}*/