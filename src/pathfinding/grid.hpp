#ifndef _GRID_H
#define _GRID_H

#include <vector>

#include "node.hpp"
#include "../world/world.hpp"

class Grid{

    public:
        Grid();
        Grid(World* world);
        
        // Fields
        World* world;
        std::vector<std::vector<Node>> nodes;
        
        // Methods
        Node GetNode(Vector2 position);
        bool containsPosition(Vector2 position);
        void InitGrid();


    private: 
        // Methods
        Node CreateNodeFromVector(Vector2 position);


};

#endif