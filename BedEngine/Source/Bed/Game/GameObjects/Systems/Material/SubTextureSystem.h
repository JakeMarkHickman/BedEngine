#pragma once

namespace Bed
{
    void SubTextureSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::SubTexture>(i))
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
    
                Bed::SubTexture* subTexture = world.GetComponent<Bed::SubTexture>(i);
    
                float textureWidth = texture->TextureSize.x;
                float textureHeight = texture->TextureSize.y;
    
                int framesPerRow = static_cast<int>(textureWidth / subTexture->TextureSize.x);
                int framesPerCol = static_cast<int>(textureHeight / subTexture->TextureSize.y);
    
                int frame = subTexture->FrameIndex;
                subTexture->LastFrame = framesPerRow * framesPerCol;
    
                int frameX = frame % framesPerRow;
                int frameY = frame / framesPerRow;
    
                subTexture->UVTopLeft.x = (frameX * subTexture->TextureSize.x) / textureWidth;
                subTexture->UVTopLeft.y = (frameY * subTexture->TextureSize.y) / textureHeight;
    
                subTexture->UVBottomRight.x = ((frameX + 1) * subTexture->TextureSize.x) / textureWidth;
                subTexture->UVBottomRight.y = ((frameY + 1) * subTexture->TextureSize.y) / textureHeight;
            }
        }
    }
}