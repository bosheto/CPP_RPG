#ifndef _PLAYER_ENTITY_H
#define _PLAYER_ENTITY_H

#include "entity.hpp"

class PlayerEntity : public Entity {

    public:
        PlayerEntity(int posX, int posY, Texture &texture, World *world);
        void Update();
    
    private:
        void HandleMouse();
        Vector2 GetMouserPos();
        
        
};

#endif