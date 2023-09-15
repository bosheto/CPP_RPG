#include "world.hpp"

World::World(int sizeX, int sizeY, Texture2D &texture){
    this->worldSizeX = sizeX;
    this->worldSizeY = sizeY;
    this->texture = texture;
    
    this->tileList = {
            GrassTile(GRASS_TILE, texture),
            StoneTile(STONE_TILE, texture)
        };
    this->tiles.resize(sizeY, std::vector<int>(sizeX));
    for(int y = 0; y < sizeY; y++){
        for(int x = 0; x < sizeX; x++){
            tiles[y][x] = tileList[0].GetId();
        }
    }
}

void World::Draw(){
    Vector2 pos;
     for(int y = 0; y < this->worldSizeX; y ++){
                for(int x = 0; x < this->worldSizeY; x++){
                    pos.x = x;
                    pos.y = y;
                    this->tileList[this->tiles[x][y]].Draw(&pos);
                }
            } 
}

void World::SetTile(int id, Vector2 postion){
    this->tiles[postion.x][postion.y] = this->tileList[id].GetId();
}



Tile World::GetTile(Vector2 position){
    return this->tileList[tiles[position.x][position.y]];

}

bool World::isTileSolid(Vector2 position){
    return tileList[tiles[position.x][position.y]].isSolid;
}

bool World::containsPosition(Vector2 position){
    if(position.x < 0 || position.x > this->worldSizeX || position.y < 0 || position.y > this->worldSizeY)
        return false;
    return true;
}