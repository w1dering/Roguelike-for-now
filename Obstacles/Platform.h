#ifndef _PLATFORM_
#define _PLATFORM_

#include <raylib.h>
#include <iostream>
#include <math.h>

#include "../Player/Player.h"

class Platform
{
public:
    Rectangle platform{0, 0, 0, 0};

    Platform(float platform_x, float platform_y, float platform_w, float platform_h)
    {
        platform.x = platform_x;
        platform.y = platform_y;
        platform.width = platform_w;
        platform.height = platform_h;
    }

    void collision(Player &player);

    float slope(float x1, float y1, float x2, float y2)
    {
        return (y2 - y1) / (x2 - x1);
    }

    float distance(float x1, float y1, float x2, float y2)
    {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }
};
#endif