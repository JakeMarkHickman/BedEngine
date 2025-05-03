#pragma once

namespace Bed
{
    void SpriteSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::Sprite>(i))
            {
                if(!world.HasComponents<Bed::Texture>(i))
                {
                    world.AttachComponents(i, Bed::Texture());
                }
    
                Bed::Texture* texture = world.GetComponent<Bed::Texture>(i);
    
                if(texture->TextureSize == 0.0f)
                {
                    continue;
                }
    
                Bed::Sprite* sprite = world.GetComponent<Bed::Sprite>(i);
    
                float textureWidth = texture->TextureSize.x;
                float textureHeight = texture->TextureSize.y;
    
                int framesPerRow = static_cast<int>(textureWidth / sprite->SpriteSize.x);
                int framesPerCol = static_cast<int>(textureHeight / sprite->SpriteSize.y);
    
                int frame = sprite->FrameIndex;
                sprite->LastFrame = framesPerRow * framesPerCol;
    
                int frameX = frame % framesPerRow;
                int frameY = frame / framesPerRow;
    
                sprite->UVTopLeft.x = (frameX * sprite->SpriteSize.x) / textureWidth;
                sprite->UVTopLeft.y = (frameY * sprite->SpriteSize.y) / textureHeight;
    
                sprite->UVBottomRight.x = ((frameX + 1) * sprite->SpriteSize.x) / textureWidth;
                sprite->UVBottomRight.y = ((frameY + 1) * sprite->SpriteSize.y) / textureHeight;
            }
        }
    }
}