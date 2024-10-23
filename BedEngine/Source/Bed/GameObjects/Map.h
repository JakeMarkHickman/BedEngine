#pragma once

#include <Bed/Core.h>
#include "ECS/ECS.h"


// TODO: BED_API
namespace Bed
{
    class BED_API Map
    {
    public:
        Map() {};
        virtual ~Map() {};

        virtual void BeginPlay() {};
        virtual void Update(float DeltaTime) 
        {
            ecs.UpdateSystems(DeltaTime);
        };

    protected:
        ECS ecs;

    private:
    };
}