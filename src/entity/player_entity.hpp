#ifndef _PLAYER_ENTITY_H
#define _PLAYER_ENTITY_H

#include "entity.hpp"
#include "unordered_map"
#include "../util/vector_util.hpp"
#include "../pathfinding/aStar.hpp"
#include <vector>
#include <list>



class PlayerEntity : public Entity {

    public:
        PlayerEntity(int posX, int posY, int speed, Texture &texture, World *world);
        void Update();
        void Draw();
        
    
    private:
        void HandleMouse();
        Vector2 GetMousePos();
        void ComputeMoveMap();
        void DrawMoveGrid();
        std::vector<Vector2> moveMap;
        std::list<Vector2> moveList;
        bool drawMoveGrid;
        A_Star pathEngine;
        int GetDistance(const Vector2& vec1, const Vector2& vec2);
};

#endif