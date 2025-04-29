#pragma once

#include <Math/Vector/Vector2.h>
#include <vector>

namespace Bed
{
    struct TileMap
    {
        TileMap(std::vector<int> mapTiles) : MapSize(10), TileSize(16), MapTiles(mapTiles) {};
        //TileMap(Bed::Vector2 mapSize = 10.0f, Bed::Vector2 tileSize = 16.0f, std::vector<int> mapTiles) : MapSize(mapSize), TileSize(tileSize), MapTiles(mapTiles) {};

        Bed::Vector2 MapSize;
        Bed::Vector2 TileSize;

        std::vector<int> MapTiles;

        std::vector<Bed::Vector2> UVTopLeft;
        std::vector<Bed::Vector2> UVBottomRight;
    };
}