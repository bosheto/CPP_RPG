#include "aStar.hpp"

#include <cstdlib>
#include <unordered_set>

#include "raymath.h"

A_Star::A_Star(World* world) : navGrid(world){
    this->world = world;
    // navGrid.world = world;
    // navGrid.InitGrid();
}

std::list<Vector2> A_Star::FindPath(Vector2 startPosition, Vector2 targetPosition){
    std::list<Node> openSet;
    std::unordered_set<Node, Node::HashFunction> closedSet;

    Node startNode = this->navGrid.GetNode(startPosition);
    Node targetNode = this->navGrid.GetNode(targetPosition);

    std::list<Vector2> path;

    openSet.push_back(startNode);

    while(openSet.size() > 0){
        // Get first node from openSet
        Node currentNode = openSet.front();

        for(int i = 1; i < openSet.size(); i ++){
            // Iterate to i index in open set
            std::list<Node>::iterator iter_node = openSet.begin();
            std::advance(iter_node, i);
            Node nodeAtIndex = *iter_node;
            
            if(nodeAtIndex.getF() < currentNode.getF() || nodeAtIndex.getF() == currentNode.getF()){
                if(nodeAtIndex.h < currentNode.h)
                    currentNode = nodeAtIndex;
            }

        }

        closedSet.insert(openSet.front());
        openSet.pop_front();

        if(currentNode == targetNode){
            path = this->RetracePath(startNode, targetNode);
            break;
        }

        for(Node neighbor : this->GetNeighbors(Vector2{float(currentNode.gridX), float(currentNode.gridY)})){
            if(!neighbor.isWalkable || closedSet.contains(neighbor)){
                continue;
            }

            int newMoveCostToNeighbor = currentNode.g + GetDistance(currentNode, neighbor);

            // Check if neighbor in openSet
            bool openSetContainsNeighbor = false;
            for(Node node : openSet){
                if(node == neighbor){
                    openSetContainsNeighbor = true;
                    break;
                }
            }

            if(newMoveCostToNeighbor < neighbor.g || !openSetContainsNeighbor){
                neighbor.g = newMoveCostToNeighbor;
                neighbor.h = this->GetDistance(neighbor, targetNode);
                neighbor.parent = &currentNode;
                if(!openSetContainsNeighbor)
                    openSet.push_front(neighbor);
            }
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
        Vector2{-1, -1},
        Vector2{ 1,  1},
        Vector2{-1,  0},
        Vector2{ 1,  0},
        Vector2{ 0,  1},
        Vector2{-1,  1},
        Vector2{ 1,  1}
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
    while(currentNode != &endNode){
        path.push_back(Vector2{float(currentNode->gridY), float(currentNode->gridY)});
        currentNode = currentNode->parent;
    }
    path.reverse();
    return path;
}