#pragma once

namespace Bed
{
    void AnimTestSystem(Bed::World& world)
    {
        for(uint64_t i : world.GetAllEntities())
        {
            if(world.HasComponents<Bed::TimerCompleted, Bed::SubTexture, Bed::EnemyTag>(i))
            {
                Bed::SubTexture* subTexture = world.GetComponent<Bed::SubTexture>(i);

                subTexture->FrameIndex++;

                subTexture->FrameIndex = subTexture->FrameIndex % subTexture->LastFrame;
            }
        }
    }
}