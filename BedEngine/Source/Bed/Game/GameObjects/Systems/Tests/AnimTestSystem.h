#pragma once

namespace Bed
{
    void AnimTestSystem(Bed::World& world)
    {
        for(int i = 0; i < world.GetAllEntities().size(); i++)
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