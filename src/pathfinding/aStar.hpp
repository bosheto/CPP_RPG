#ifndef _A_STAR_H
#define _A_STAR_H

#include <list>

#include "grid.hpp"
#include "../world/world.hpp"

class A_Star{

    public:
        A_Star(World *world);
        
        // Methods
        std::list<Vector2> FindPath(const Vector2 startPosition, const Vector2 targetPosition);

    private:
        // Fields
        World* world;
        Grid navGrid;

        // Methods
        int GetDistance(Node a, Node b);
        std::list<Node> GetNeighbors(Vector2 position);
      
        std::list<Vector2> RetracePath(Node startNode, Node endNode);

};


#endif