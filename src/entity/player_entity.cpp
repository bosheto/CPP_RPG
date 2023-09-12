#include "player_entity.hpp"

PlayerEntity::PlayerEntity(int x, int y, Texture &texture, World *world) : Entity(0,1, x, y, texture, world){
    Entity::SetWalkAnimationFrames(0,1,3);
}

Vector2 PlayerEntity::GetMouserPos(){
    Vector2 mousePosition = GetMousePosition();
    int mouseX = int(mousePosition.x) / SPRITE_SIZE;
    int mouseY = int(mousePosition.y) / SPRITE_SIZE;
    return Vector2{float(mouseX), float(mouseY)};
}

void PlayerEntity::HandleMouse(){
    if(IsMouseButtonReleased(0)){
        Entity::Move(this->GetMouserPos());
    }
}

void PlayerEntity::Update(){
    this->HandleMouse();
    Entity::Update();
}
