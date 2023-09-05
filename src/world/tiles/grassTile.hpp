#ifndef _GRASS_TILE_H
#define _GRASS_TILE_H

#include "../tile.hpp"

class GrassTile : public Tile{
    public:
        GrassTile(int id, Texture2D &texture);
};

#endif