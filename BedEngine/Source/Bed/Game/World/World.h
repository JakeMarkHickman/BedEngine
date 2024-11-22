#pragma once

#include <Bed/Core.h>
#include <iostream>

namespace Bed
{
    class BED_API World
    {
    public:
        World() {};
        virtual ~World() {};

        virtual void BeginPlay() {};
        virtual void Update(float deltaTime) {};
    
    protected:
    };
}