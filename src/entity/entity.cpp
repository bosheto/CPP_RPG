#include "entity.hpp"

Entity::Entity(int spriteX, int spriteY, int posX, int posY, int speed, Texture &texture, World *world){
    this->position.x = posX * SPRITE_SIZE;
    this->position.y = posY * SPRITE_SIZE;
    this->spriteRectangle.height = SPRITE_SIZE;
    this->spriteRectangle.width = SPRITE_SIZE;
    this->spriteRectangle.x = spriteX * SPRITE_SIZE;
    this->spriteRectangle.y = spriteY * SPRITE_SIZE;
    this->texture = texture;
    this->world = world;
    this->speed = speed;
}

Texture Entity::GetTexture(){
    return this->texture;
}

bool Entity::IsMoving(){
    return this->isMoving;
}

void Entity::SetWalkAnimationFrames(int startX, int startY, int endX){
    int numberOfFrames = endX - startX;
    for(int i=0; i < numberOfFrames; i++){
        Rectangle animationFrame;
            animationFrame.x = (startX + i) * SPRITE_SIZE;
            animationFrame.y = startY * SPRITE_SIZE;
            animationFrame.width = SPRITE_SIZE;
            animationFrame.height = SPRITE_SIZE;
        
        this->walkAnimationList.push_back(animationFrame);
    }
}

void Entity::SetPosition(int x, int y){
    this->position.x = x;
    this->position.y = y;
    this->moveTargetPosition = this->position;
}

void Entity::Draw(){
    if(this->isMoving && this->walkAnimationList.size() > 0){
        if(this->current_walk_frame > this->walkAnimationList.size()-1){
            this->current_walk_frame = 0;
        }
       DrawTextureRec(this->texture, this->walkAnimationList[this->current_walk_frame], this->position, WHITE);
    }else{
        DrawTextureRec(this->texture, this->spriteRectangle, this->position, WHITE);
    }
}

Vector2 Entity::GetPosition(){
    int posX = this->position.x / SPRITE_SIZE;
    int posY = this->position.y / SPRITE_SIZE;
    return Vector2{float(posX), float(posY)};
}

World* Entity::GetWorld(){
    return this->world;
}

void Entity::Move(std::list<Vector2> moves){
    if(!isMoving){    
        this->isMoving = true;
        int entityX = int(this->position.x) / SPRITE_SIZE;
        int entityY = int(this->position.y) / SPRITE_SIZE;
        this->moveList = moves;
        this->moveTargetPosition = moveList.front();
    }
}

int Entity::GetSpeed(){
    return this->speed;
}

void Entity::move(){
    Vector2 direction = Vector2Normalize(Vector2Subtract(this->moveTargetPosition, this->position)); 
    direction.x = std::round(direction.x);
    direction.y = std::round(direction.y);
    if(Vector2Equals(this->position, moveTargetPosition)){
        if(this->moveList.size() == 0){
            this->isMoving = false;
            this->lastUpdate = 0.0;
            this->moveTargetPosition = this->position;
            return;
        }else{
            this->moveList.erase(this->moveList.begin());
            if(this->moveList.size() > 0){
                this->moveTargetPosition = this->moveList.front();
            }
        }

    }


    if(GetTime()-this->lastUpdate >= MOVE_TIME_STEP){

        this->position.x += direction.x * MOVE_INCREMENT;
        this->position.y += direction.y * MOVE_INCREMENT;
        this->current_walk_frame += 1;
        this->lastUpdate = GetTime();
    }
    
}

void Entity::Update(){
    move();
}