#include "raylib.h"
#include "raymath.h"
#include "world/tile.hpp"
#include "world/tiles/grassTile.hpp"
#include "world/tiles/stoneTile.hpp"
#include "world/world.hpp"

#include "entity/entity.hpp"
#include "pathfinding/aStar.hpp"


#include <vector>
#include <iostream>

int main(int argc, char ** argv){

    InitWindow(800, 600, "Template 4-5-0");
    SetTargetFPS(30);


    Image spriteSheet = LoadImage("assets/SpriteSheet-export.png");
    Texture2D tex2d = LoadTextureFromImage(spriteSheet);
    Texture2D* P_tex2d = &tex2d;

    World world = World(25,25, *P_tex2d);

    

    world.SetTile(STONE_TILE, Vector2{1,0});
    world.SetTile(STONE_TILE, Vector2{1,1});
    world.SetTile(STONE_TILE, Vector2{1,2});
    world.SetTile(STONE_TILE, Vector2{1,3});
    world.SetTile(STONE_TILE, Vector2{1,4});
    world.SetTile(STONE_TILE, Vector2{1,5});

    Entity player = Entity(0,1, 0,0, *P_tex2d);
    player.SetWalkAnimationFrames(0,1,3);

    Rectangle rect;
    rect.x = 0;
    rect.y = 0;
    rect.height=32;
    rect.width = 32;

    Vector2 pos;

    std::list<Vector2> moveList;
    moveList.push_back(Vector2{0,32});
    moveList.push_back(Vector2{32,32});
    moveList.push_back(Vector2{64,32});
    moveList.push_back(Vector2{64,64});
    
    A_Star aStar = A_Star(&world);



    while(!WindowShouldClose()){
        
        if(IsKeyDown(KEY_A)) {
            std::list<Vector2> t = aStar.FindPath(Vector2{0,0}, Vector2{0,1});
            player.Move(t);
        }
        if(IsKeyDown(KEY_B)) player.SetPosition(0,0);
        BeginDrawing();
            ClearBackground(BLACK);
            world.Draw();
            player.Update();
        EndDrawing();
    }
    
    return 0;
}