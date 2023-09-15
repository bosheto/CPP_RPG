#ifndef _VECTOR_UTIL_H
#define _VECTOR_UTIL_H

#include "raylib.h"
#include <iostream>
#include <functional> // For std::hash

#include "../globals.hpp"

struct Vector2Hash {
    size_t operator()(const Vector2* v) const {
        // Use a combination of the hashes of x and y
       std::size_t vecXHash = std::hash<float>{}(v->x);
       std::size_t vecYHash = std::hash<float>{}(v->y);
       return vecXHash ^ (vecYHash << 1);
    }
};


#endif