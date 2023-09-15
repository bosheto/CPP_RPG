#include "position.hpp"

Position::Position(int x, int y){
    this->x = x;
    this->y = y;
}

Position::Position(Vector2 vec){
    this->x = int(vec.x);
    this->y = int(vec.y);
}

Position::~Position(){

}

int Position::GetX(){
    return this->x;
}

int Position::GetY(){
    return this->y;
}

void Position::SetX(int x){
    this->x = x;
}

void Position::SetY(int y){
    this->y = y;
}

