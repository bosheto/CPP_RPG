#ifndef _WORLD_H
#define _WORLD_H
#include "tile.hpp"
#include "tiles/grassTile.hpp"
#include "tiles/stoneTile.hpp"
#include <vector>

#define GRASS_TILE 0
#define STONE_TILE 1

class World{
    public:
        World(int sizeX, int sizeY, Texture2D &texture);
        Texture2D texture;
        void Draw();
        void Update();
        
        int GetSizeX() {return worldSizeX;};
        int GetSizeY() {return worldSizeY;};
        
        Tile GetTile(Vector2 position);
        void SetTile(int id, Vector2 position);

    private:
        int worldSizeX;
        int worldSizeY;
        std::vector<std::vector<int>> tiles;
        std::vector<Tile> tileList;
};

#endif