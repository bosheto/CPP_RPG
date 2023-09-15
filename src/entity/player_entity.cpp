#include "player_entity.hpp"
#include <iostream>
PlayerEntity::PlayerEntity(int x, int y, Texture &texture, World *world) : Entity(0,1, x, y, 5, texture, world), pathEngine(world){
    Entity::SetWalkAnimationFrames(0,1,3);
    this->drawMoveGrid = false;
}

Vector2 PlayerEntity::GetMousePos(){
    Vector2 mousePosition = GetMousePosition();
    int mouseX = int(mousePosition.x) / SPRITE_SIZE;
    int mouseY = int(mousePosition.y) / SPRITE_SIZE;
    return Vector2{float(mouseX), float(mouseY)};
}

void PlayerEntity::HandleMouse(){
    if(IsMouseButtonDown(0)){
        Vector2 target = this->GetMousePos();
        int dist =  this->GetDistance(this->GetPosition(), target) <= this->GetSpeed();
        if(!this->IsMoving() && dist <= this->GetSpeed())
            if(!this->GetWorld()->GetTile(target).isSolid){
                this->moveList = this->pathEngine.FindPath(this->GetPosition(), target);
                if(this->moveList.size() > this->GetSpeed() + 1){
                    this->moveList.resize(this->GetSpeed() + 1);
            }
        }
            this->ComputeMoveMap();

        drawMoveGrid = true;
    }
    if(IsMouseButtonReleased(0)){
        Entity::Move(this->moveList);
    }
}

void PlayerEntity::ComputeMoveMap(){
    this->moveMap.clear();
    for(int y = -this->GetSpeed(); y <= this->GetSpeed(); y++){
        for(int x = -this->GetSpeed(); x <= this->GetSpeed(); x++){
            Vector2 possibleMove = Vector2Add(this->GetPosition(), Vector2{float(x), float(y)});
            if(!this->GetWorld()->containsPosition(possibleMove))
                continue;
            this->moveMap.push_back(possibleMove);
        }
    }
}

void PlayerEntity::DrawMoveGrid(){
    Rectangle rect;
    rect.x = 2 * SPRITE_SIZE;
    rect.y = 2 * SPRITE_SIZE;
    rect.height = SPRITE_SIZE;
    rect.width = SPRITE_SIZE;


    for(int i=0; i < this->moveMap.size(); i++){
        Vector2 pos = Vector2{float(moveMap[i].x * SPRITE_SIZE), float(moveMap[i].y * SPRITE_SIZE)};
        Color color = GREEN;
        if(this->GetWorld()->GetTile(this->moveMap[i]).isSolid)
            color = RED;
        for(const Vector2& elem : this->moveList){
            if(elem.x == pos.x && elem.y == pos.y){
                color = BLUE;
                break;
            }
        }
        
        DrawTextureRec(this->GetTexture(), rect, pos , color);
    }


}

void PlayerEntity::Update(){
    
    this->HandleMouse();
    Entity::Update();
}

void PlayerEntity::Draw(){
    if(this->drawMoveGrid){
        this->DrawMoveGrid();
        this->drawMoveGrid = false;
    }
    Entity::Draw();
}

int PlayerEntity::GetDistance(const Vector2& vec1, const Vector2& vec2){
    int dx = std::pow(vec2.x - vec1.x, 2);
    int dy = std::pow(vec2.y - vec1.y, 2);
    double dist = std::sqrt(dx + dy);
    return int(dist);
}