#pragma once

namespace Bed
{
    struct PlayerTag {
        PlayerTag(int id, float speed) : ID(id), Speed(speed) {}; 
        int ID = 0;
        float Speed = 10.0f;
    };
}