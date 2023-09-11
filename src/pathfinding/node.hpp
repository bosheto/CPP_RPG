#ifndef _NODE_H
#define _NODE_H

#include "raylib.h"
#include <functional> // For std::hash
class Node {
    public:
        // Fields
        Node *parent = nullptr;
        bool isWalkable;
        Vector2 position;
        int gridX = 0;
        int gridY = 0;
        int g = 0;
        int h = 0;
        
        // Constructors
        Node();
        Node(bool isWalkable, const Vector2 position);

        // Methods
        int getF(){ return g + h; };
        
        // Operators
        bool operator==(const Node& other) const {
            return this->gridX == other.gridX && this->gridY == other.gridY;
        }

        bool operator!=(const Node& other){
            return this->gridX != other.gridX || this->gridY != other.gridY; 
        }

         // Define a hash function for Node
        struct HashFunction {
            std::size_t operator()(const Node* node) const {
                // Use a combination of hash values for gridX and gridY
                std::size_t gridXHash = std::hash<int>{}(node->gridX);
                std::size_t gridYHash = std::hash<int>{}(node->gridY);
                
                // Combine the hash values using a simple bitwise operation (XOR)
                return gridXHash ^ (gridYHash << 1);
            }
        };

};

#endif

