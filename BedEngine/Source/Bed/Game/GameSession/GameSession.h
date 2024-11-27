#pragma once

#include <Bed/Core.h>

//This needs to be edited as this will hold data that will be persistant across the game without a need to save
namespace Bed
{
    class BED_API GameSession
    {
    public:
        GameSession() {};
        ~GameSession() {};
    };
}