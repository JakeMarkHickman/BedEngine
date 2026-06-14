#pragma once

#include <SleepTrace.h>
#include <App/Time.h>

namespace Bed
{
    void OnUVAnimationComponentAttached(Bed::World& world, uint64_t entity)
    {
        if(world.HasComponents<Bed::UVAnimation>(entity))
        {
            if(!world.HasComponents<Bed::Texture>(entity))
            {
                
            }
        }
    }

    void UVAnimationSystem(Bed::World& world)
    {
        for(uint64_t entity : world.GetAllEntities())
        {
            if(world.HasComponents<Bed::Texture, Bed::UVAnimation>(entity))
            {
                Bed::Texture* texture = world.GetComponent<Bed::Texture>(entity);
                Bed::UVAnimation* anim = world.GetComponent<Bed::UVAnimation>(entity);

                if((anim->CurrentFrame > (anim->Frames.size() - 1)) && (!anim->Looping))
                {
                    continue;
                }

                anim->CurrentTime += Bed::Time::GetDeltaTime();

                if(anim->CurrentTime >= 1.0f / anim->FPS)
                {
                    anim->CurrentTime = 0.0f;
                    anim->CurrentFrame = anim->CurrentFrame % anim->Frames.size();

                    texture->MinUV = anim->Frames[anim->CurrentFrame].UVMin; 
                    texture->MaxUV = anim->Frames[anim->CurrentFrame].UVMax;
                    texture->TexturePath = anim->Frames[anim->CurrentFrame].TexturePath;

                    anim->CurrentFrame++;
                }
            }
        }
    }
}