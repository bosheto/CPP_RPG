#ifndef _STONE_TILE_H
#define _STONE_TILE_H

#include "../tile.hpp"

class StoneTile : public Tile {
    public:
        StoneTile(int id, Texture2D &texture);
};

#endif