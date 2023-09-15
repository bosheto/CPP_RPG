#include "raylib.h"
#include "raymath.h"
#include "world/world.hpp"

#include "entity/player_entity.hpp"

#include <vector>
#include <iostream>
#include <cmath>

int main(int argc, char ** argv){

    InitWindow(800, 600, "Template 4-5-0");
    SetTargetFPS(30);


    Image spriteSheet = LoadImage("assets/SpriteSheet-export.png");
    Texture2D tex2d = LoadTextureFromImage(spriteSheet);
    Texture2D* P_tex2d = &tex2d;

    World world = World(25,25, *P_tex2d);
    World* pWorld = &world;
    world.SetTile(STONE_TILE, Vector2{1,0});
    world.SetTile(STONE_TILE, Vector2{1,1});
    world.SetTile(STONE_TILE, Vector2{1,2});
    world.SetTile(STONE_TILE, Vector2{1,3});
    world.SetTile(STONE_TILE, Vector2{1,4});
    world.SetTile(STONE_TILE, Vector2{1,5});

    PlayerEntity player = PlayerEntity(0,0, *P_tex2d, &world);

    while(!WindowShouldClose()){

        player.Update();

        BeginDrawing();
            ClearBackground(BLACK);
            world.Draw();
            player.Draw();
        EndDrawing();
    }
    
    return 0;
}