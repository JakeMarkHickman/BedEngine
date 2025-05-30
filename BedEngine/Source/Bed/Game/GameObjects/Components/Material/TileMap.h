#pragma once

#include <Math/Vector/Vector2.h>
#include <vector>

namespace Bed
{
    struct TileMap
    {
        TileMap(std::vector<int> mapTiles) : MapSize(10), TileSize(16), MapTiles(mapTiles) {};
        //TileMap(Bed::Vector2 mapSize = 10.0f, Bed::Vector2 tileSize = 16.0f, std::vector<int> mapTiles) : MapSize(mapSize), TileSize(tileSize), MapTiles(mapTiles) {};

        Pillow::Vector2f MapSize;
        Pillow::Vector2f TileSize;

        std::vector<int> MapTiles;

        std::vector<Pillow::Vector2f> UVTopLeft;
        std::vector<Pillow::Vector2f> UVBottomRight;
    };
}