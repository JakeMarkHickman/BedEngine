#pragma once

namespace Bed
{
    void AnimTestSystem(Bed::World& world)
    {
        for(int i = 0; i < world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::TimerCompleted, Bed::Sprite, Bed::EnemyTag>(i))
            {
                Bed::Sprite* sprite = world.GetComponent<Bed::Sprite>(i);

                sprite->FrameIndex++;

                sprite->FrameIndex = sprite->FrameIndex % sprite->LastFrame;
            }
        }
    }
}