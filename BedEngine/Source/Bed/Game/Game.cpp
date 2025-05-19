#include "Game.h"

Bed::Game::Game()
{
    BeginPlay();
}

void Bed::Game::Update() 
{ 
    m_ecs.UpdateSystems();
};