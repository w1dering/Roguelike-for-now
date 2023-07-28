#ifndef _PLATFORM_
#define _PLATFORM_

#include <raylib.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "../Player/Player.h"

using namespace std;

class Platform
{
public:
    Rectangle dimensions{0, 0, 0, 0};

    bool canMove = false;
    int periodLength = 0;
    int currentFrame;
    float speed_x = 0;
    float speed_y = 0;

    bool spikes[4] = {false, false, false, false};
    // will be t b l r in that order

    vector<Vector3> movement;
    // movement[i].x = acceleration in x
    // movement[i].y = acceleration in y
    // movement[i].z = number of frames of phase

    Platform(float platform_x, float platform_y, float platform_w, float platform_h) // no movement, no spikes
    {
        dimensions.x = platform_x;
        dimensions.y = platform_y;
        dimensions.width = platform_w;
        dimensions.height = platform_h;
    }

    Platform(float platform_x, float platform_y, float platform_w, float platform_h, vector<Vector3> movementParam) // movement, no spikes
    {
        dimensions.x = platform_x;
        dimensions.y = platform_y;
        dimensions.width = platform_w;
        dimensions.height = platform_h;
        canMove = true;

        currentFrame = 0;
        movement = movementParam;
        speed_x = 0;
        speed_y = 0;

        for (int i = 0; i < (int)movement.size(); i++)
        {
            periodLength += movement[i].z;
        }
    }

    Platform(float platform_x, float platform_y, float platform_w, float platform_h, vector<bool> spikesParam) // spiked, no movement
    {
        dimensions.x = platform_x;
        dimensions.y = platform_y;
        dimensions.width = platform_w;
        dimensions.height = platform_h;

        for (int i = 0; i < 4; i++)
        {
            spikes[i] = spikesParam[i];
        }
    }

    Platform(float platform_x, float platform_y, float platform_w, float platform_h, vector<Vector3> movementParam, vector<bool> spikesParam) // movement, no spikes
    {
        dimensions.x = platform_x;
        dimensions.y = platform_y;
        dimensions.width = platform_w;
        dimensions.height = platform_h;
        canMove = true;

        for (int i = 0; i < 4; i++)
        {
            spikes[i] = spikesParam[i];
        }

        currentFrame = 0;
        movement = movementParam;
        speed_x = 0;
        speed_y = 0;

        for (int i = 0; i < (int)movement.size(); i++)
        {
            periodLength += movement[i].z;
        }
    }

    void collision(Player &player);

    void movePlatform();

    inline float slope(float x1, float y1, float x2, float y2)
    {
        return (y2 - y1) / (x2 - x1);
    }

    float distance(float x1, float y1, float x2, float y2)
    {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }
};
#endif