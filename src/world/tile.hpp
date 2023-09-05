#ifndef _TILE_H
#define _TILE_H

#include <string>
// #include "raylib.h"
#include "../globals.hpp"

class Tile{
    public:
        Tile(int id, int spriteX, int spriteY, std::string name, Texture2D &texture,bool isSolid);
        void Draw(Vector2* position);
        int GetId() {return id;};
        bool isSolid;
    private:
        int id;
        int spriteX;
        int spriteY;
        std::string name;
        Texture2D texture;
        Rectangle spriteRectangle;
};

#endif