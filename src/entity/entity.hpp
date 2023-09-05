#ifndef _ENTITY_H
#define _ENTITY_H

#include "../globals.hpp"
#include "raymath.h"
#include <list>
#include <vector>

class Entity{
    public:
       
        Entity(int spriteX, int spriteY, int posX, int posY, Texture &texture);
        // FIXME change this 
        Vector2 GetPosition();
        void Update();
        void Move(std::list<Vector2>targetPositionList);
        void SetPosition(int x, int y);
        void SetWalkAnimationFrames(int startX, int startY, int endX);

    private:

        std::vector<Rectangle> walkAnimationList;
        int current_walk_frame = 0;
    
        Vector2 moveTargetPosition;
        Vector2 position;
        Rectangle spriteRectangle;
        Texture texture;
        bool isMoving = false;
        float lastUpdate = 0.0;
        std::list<Vector2> moveList;
        void Draw();
        void move();
};

#endif