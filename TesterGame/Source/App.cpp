
#include <BedEngineApplication.h>

// TODO: Make this able to be editied by the editor when creating project

class TesterGame : public Bed::Application
{

};

Bed::Application* CreateApplication()
{
    return new TesterGame;
}