#ifndef _POSITION_H
#define _POSITION_H

#include <functional>
#include "raylib.h"
#include "../globals.hpp"

class Position {

    public:
        Position(int x, int y);
        Position(Vector2 vec);
        ~Position();

        int GetX();
        int GetY();
        void SetX(int);
        void SetY(int);

        static Vector2 toVector(Position pos) {
            return Vector2{float(pos.GetX()), float(pos.GetY())};
        };
        static Position toWorldPosition(Vector2 vec) {
            return Position(vec);
        };

        bool operator==(const Position& other) const {
            return this->x == other.x && this->y == other.y;
        }

        bool operator!=(const Position& other) const {
            return this->x != other.x || this->y != other.y;
        }

        Position operator+(const Position& other) const{
            return Position(this->x + other.x, this->y + other.y);
        };

        struct HashPosition {
            std::size_t operator()(const Position* pos) const {
                std::size_t gridXHash = std::hash<int>{}(pos->x);
                std::size_t gridYHash = std::hash<int>{}(pos->y);
                return gridXHash ^ (gridYHash << 1);
            }
        };



    private:
        int x;
        int y;

};

#endif