#pragma once

namespace Playground
{
    struct Player
    {
        Player(int id, float speed) : ID(id), Speed(speed) {}; 
        int ID = 0;
        float Speed = 10.0f;
    };
}