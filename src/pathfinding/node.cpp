#include "node.hpp"

Node::Node(){
    this->isWalkable = false;
    this->position = Vector2{-1,-1};
}

Node::Node(bool isWalkable, Vector2 position){
    this->isWalkable = isWalkable;
    this->position = position;
}