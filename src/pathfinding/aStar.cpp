#include "aStar.hpp"

#include <cstdlib>
#include <unordered_set>

#include "raymath.h"
#include "../globals.hpp"

A_Star::A_Star(World *world) : navGrid(world){
    this->world = world;
    navGrid.world = world;
    navGrid.InitGrid();
}

std::list<Vector2> A_Star::FindPath(const Vector2 startPosition, const Vector2 targetPosition){
    // Nodes to evaluate 
    std::list<Node*> openSet;
    // Evaluated nodes 
    std::unordered_set<Node*, Node::HashFunction> closedSet;

    Node startNode = this->navGrid.GetNode(startPosition);
    Node targetNode = this->navGrid.GetNode(targetPosition);

    // Path to return 
    std::list<Vector2> path;

    openSet.push_back(&startNode);

    while(openSet.size() > 0){
        // Get first node from openSet
        Node* currentNode = openSet.front();

        for(int i = 1; i < openSet.size(); i ++){
            // Iterate to i index in open set
            std::list<Node*>::iterator iter_node = openSet.begin();
            std::advance(iter_node, i);
            Node* nodeAtIndex = *iter_node;
            
            if(nodeAtIndex->getF() < currentNode->getF() || nodeAtIndex->getF() == currentNode->getF() && nodeAtIndex->h < currentNode->h){
                currentNode = nodeAtIndex;
            }

        }

        openSet.remove(currentNode);
        closedSet.insert(currentNode);

        if(*currentNode == targetNode){
            path = this->RetracePath(startNode, *currentNode);
            break;
        }
        
        std::list<Node> neighbors = this->GetNeighbors(Vector2{float(currentNode->gridX), float(currentNode->gridY)});

        for(Node neighbor : neighbors){
            Node *t = new Node(neighbor.isWalkable, neighbor.position);
            t->gridX = neighbor.gridX;
            t->gridY = neighbor.gridY;
            t->h = neighbor.h;
            t->g = neighbor.g;


            if(!neighbor.isWalkable || closedSet.contains(&neighbor)){
                delete(t);
                continue;
            }

            int newMoveCostToNeighbor = currentNode->g + GetDistance(*currentNode, neighbor);

            // Check if neighbor in openSet
            bool openSetContainsNeighbor = false;
            for(Node* node : openSet){
                if(*node == neighbor){
                    openSetContainsNeighbor = true;
                    break;
                }
            }

            if(newMoveCostToNeighbor < neighbor.g || !openSetContainsNeighbor){
                t->g = newMoveCostToNeighbor;
                t->h = this->GetDistance(neighbor, targetNode);
                t->parent = currentNode;
                if(!openSetContainsNeighbor)
                    openSet.push_front(t);
                    continue;
            }
            delete(t);
        }
    }
    return path;
}


int A_Star::GetDistance(Node a, Node b){
    int distX = std::abs(a.gridX - b.gridX);
    int distY = std::abs(a.gridY - b.gridY);

    if(distX > distY)
        return 14 * distY + 10 * (distX - distY);
    return 14 * distX + 10 * (distY - distX);
}

std::list<Node> A_Star::GetNeighbors(Vector2 position){
    std::list<Node> neighbors;
    Vector2 neighborPositions[8] = {
        Vector2{ 0, -1},
        Vector2{ 0,  1},
        Vector2{ 1,  0},
        Vector2{-1,  0},
        Vector2{ 1,  1},
        Vector2{-1,  1},
        Vector2{ 1, -1},
        Vector2{-1, -1}
    };

    for(Vector2 n_position : neighborPositions){
        Vector2 testPosition = Vector2Add(position, n_position);
        if(this->navGrid.containsPosition(testPosition))
            neighbors.push_back(this->navGrid.GetNode(testPosition));
    }

    return neighbors;
}

std::list<Vector2> A_Star::RetracePath(Node startNode, Node endNode){
    std::list<Vector2> path;
    Node* currentNode = &endNode;
    while(currentNode != nullptr){
        path.push_back(Vector2{float(currentNode->gridX * SPRITE_SIZE), float(currentNode->gridY * SPRITE_SIZE)});
        currentNode = currentNode->parent;
    }
    path.reverse();
    return path;
}