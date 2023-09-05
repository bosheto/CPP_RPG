#include "grid.hpp"

Grid::Grid(World* world){
    this->world = world;
    this->InitGrid();
}

Grid::Grid(){}

void Grid::InitGrid(){
    this->nodes.resize(this->world->GetSizeX(), std::vector<Node>(this->world->GetSizeY()));
    for(int y = 0; y < this->world->GetSizeY(); y++){
        for(int x = 0; x < this->world->GetSizeX(); x++){
            nodes[y][x] = this->CreateNodeFromVector(Vector2{float(x), float(y)});
        }
    }
}

Node Grid::CreateNodeFromVector(Vector2 position){
    Node node = Node();
    node.gridX = position.x;
    node.gridY = position.y;
    node.isWalkable = !this->world->GetTile(position).isSolid;
    return node;
}

Node Grid::GetNode(Vector2  position){
    if(this->containsPosition(position))
        return nodes[position.y][position.x];
    return Node();
}

bool Grid::containsPosition(Vector2 position){
    if(position.x < 0 || position.x >= nodes[0].size())
        return false;
    return position.y > 0 && position.y < nodes.size();
}