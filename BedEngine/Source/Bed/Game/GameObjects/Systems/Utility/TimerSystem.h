#pragma once

#include <App/Time.h>
#include <Components/Event/Timer/TimerCompleted.h>

namespace Bed
{
    void TimerSystem(Bed::World& world)
    {
        //TODO: Get all Entities will break if entites are removed
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::TimerCompleted>(i))
            {
                world.RemoveComponents<Bed::TimerCompleted>(i);
            }

            if(world.HasComponents<Bed::Timer>(i))
            {
                Bed::Timer* timer = world.GetComponent<Bed::Timer>(i);

                if(timer->IsActive)
                {
                    timer->Elapsed += Bed::Time::GetDeltaTime();

                    if(timer->Elapsed >= timer->Duration)
                    {
                        if(!timer->IsLooping)
                        {
                            timer->IsActive = false;
                        }

                        timer->Elapsed = 0.0f;
                        
                        world.AttachComponents(i, Bed::TimerCompleted());
                    }
                }
            }
        }
    }
}