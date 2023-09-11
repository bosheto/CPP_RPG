#include "node.hpp"

Node::Node(){
    this->isWalkable = false;
    
}

Node::Node(bool isWalkable, const Vector2 position){
    this->isWalkable = isWalkable;
    this->position = position;
}
