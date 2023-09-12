#ifndef _ENTITY_H
#define _ENTITY_H

#include "../globals.hpp"
#include "raymath.h"
#include "../world/world.hpp"
#include "../pathfinding/aStar.hpp"
#include <list>
#include <vector>
#include <cmath>


class Entity{
    public:
       
        Entity(int spriteX, int spriteY, int posX, int posY, Texture &texture, World *world);
        // FIXME change this 
        Vector2 GetPosition();
        void Update();
        void Move(Vector2 targetPosition);
        void SetPosition(int x, int y);
        void SetWalkAnimationFrames(int startX, int startY, int endX);
        void Draw();

    private:

        std::vector<Rectangle> walkAnimationList;
        int current_walk_frame = 0;
        World *world;
        A_Star pathEngine;
        Vector2 moveTargetPosition;
        Vector2 position;
        Rectangle spriteRectangle;
        Texture texture;
        bool isMoving = false;
        float lastUpdate = 0.0;
        std::list<Vector2> moveList;
        void move();
};

#endif