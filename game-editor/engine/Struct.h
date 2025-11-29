#pragma once
#include "SDL.h"


struct Vec2
{
    float x, y;
};

struct Vec3
{
    float x, y, z;
};

struct Triangle
{
    SDL_FPoint v1, v2, v3;
    SDL_Color color;
};
