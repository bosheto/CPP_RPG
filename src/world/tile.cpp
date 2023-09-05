#include "tile.hpp"

// Tile::Tile() : id(0), spriteX(1), spriteY(1), name("debug");

Tile::Tile(int id, int spriteX, int spriteY, std::string name, Texture2D &texture, bool isSolid){
    this->name = name;
    this-> spriteX = spriteX;
    this-> spriteY = spriteY;
    this->id = id;
    this->texture = texture;
    this->spriteRectangle.x = spriteX * SPRITE_SIZE;
    this->spriteRectangle.y = spriteY * SPRITE_SIZE;
    this->spriteRectangle.height = SPRITE_SIZE;
    this->spriteRectangle.width = SPRITE_SIZE;
    this->isSolid = isSolid;
}

void Tile::Draw(Vector2* position){

    Vector2 positionToDraw;
    positionToDraw.x = position->x * SPRITE_SIZE;
    positionToDraw.y = position->y * SPRITE_SIZE;

    DrawTextureRec(this->texture, this->spriteRectangle, positionToDraw, WHITE);


}