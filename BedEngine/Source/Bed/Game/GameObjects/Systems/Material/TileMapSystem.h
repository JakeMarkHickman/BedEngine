#pragma once

namespace Bed
{

    //TODO: finish this
    void TileMapSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::TileMap>(i))
            {
                if(!world.HasComponents<Bed::Transform>(i))
                {
                    world.AttachComponents(i, Bed::Transform(0.0f, 0.0f, 1.0f));
                }

                if(!world.HasComponents<Bed::Texture>(i))
                {
                    world.AttachComponents(i, Bed::Texture());
                }

                Bed::TileMap* tileMap = world.GetComponent<Bed::TileMap>(i);
                Bed::Texture* texture = world.GetComponent<Bed::Texture>(i);
                Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);

                if(texture->TextureSize == 0.0f)
                {
                    continue;
                }

                for(int y = 0; y < tileMap->MapSize.y; y++)
                {
                    for(int x = 0; x < tileMap->MapSize.x; x++)
                    {
                        int tileID = tileMap->MapTiles[y * tileMap->MapSize.x + x];
                        if(tileID < 0) continue;

                        Bed::Vector2 tilePosition = Bed::Vector2(transform->Position.x, transform->Position.y) + Bed::Vector2(x * tileMap->TileSize.x, y * tileMap->TileSize.y);

                        int tilesPerRow = texture->TextureSize.x / tileMap->TileSize.x;
                        int tileX = tileID % tilesPerRow;
                        int tileY = tileID / tilesPerRow; 

                        //TODO: add this to array of UVs in tileMap Component

                        float U0 = (tileX * tileMap->TileSize.x) / texture->TextureSize.x;
                        float V0 = 1.0f - (tileY * tileMap->TileSize.y) / texture->TextureSize.y;
    
                        float U1 = ((tileX + 1) * tileMap->TileSize.x) / texture->TextureSize.x;
                        float V1 = 1.0f - ((tileY + 1) * tileMap->TileSize.y) / texture->TextureSize.y;

                        std::cout << U0 << " " << V0 << " : " << U1 << " " << V1 << "\n";
                    }
                }
            }
        }
    }
}