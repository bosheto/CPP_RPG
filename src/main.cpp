#include "raylib.h"
#include "raymath.h"
#include "world/world.hpp"
#include <nlohmann/json.hpp>
#include "entity/player_entity.hpp"

#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

int main(int argc, char ** argv){
    

    // std::ofstream outFile("./out.json");
    // std::vector<int> world1 = {0,1,2,3,4,5,6};
    // std::vector<int> world2 = {10,11,12,13,14,15,16};
    // std::vector<std::vector<int>> world = {world1, world2};

    // nlohmann::json newJson;
    // newJson["world"] = world;

    // outFile << newJson;

    // std::ifstream inFile("./out.json");
    // nlohmann::json file = nlohmann::json::parse(inFile);
    // auto posX = file["world"][1];
    // std::cout << posX[1] << std::endl;

    InitWindow(800, 600, "Template 4-5-0");
    SetTargetFPS(30);


    Image spriteSheet = LoadImage("assets/SpriteSheet-export.png");
    Texture2D tex2d = LoadTextureFromImage(spriteSheet);
    Texture2D* P_tex2d = &tex2d;

    World world = World(25,25, *P_tex2d);
    world.LoadLevel("level_dev"); 
    World* pWorld = &world;

    PlayerEntity player = PlayerEntity(0,0, 10, *P_tex2d, &world);

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