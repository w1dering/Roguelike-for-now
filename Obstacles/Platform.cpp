#include <raylib.h>
#include <iostream>

#include "Platform.h"
#include "Trapezoid.h"

void Platform::collision(Player &player)
{
    Vector2 boundTL{dimensions.x - player.width / (float)2.0, dimensions.y - player.height / (float)2.0};
    Vector2 boundTR{dimensions.x + dimensions.width + player.width / (float)2.0, dimensions.y - player.height / (float)2.0};
    Vector2 boundBL{dimensions.x - player.width / (float)2.0, dimensions.y + dimensions.height + player.height / (float)2.0};
    Vector2 boundBR{dimensions.x + dimensions.width + player.width / (float)2.0, dimensions.y + dimensions.height + player.height / (float)2.0};

    Vector2 platTL{dimensions.x, dimensions.y};
    Vector2 platTR{dimensions.x + dimensions.width, dimensions.y};
    Vector2 platBL{dimensions.x, dimensions.y + dimensions.height};
    Vector2 platBR{dimensions.x + dimensions.width, dimensions.y + dimensions.height};

    Trapezoid topRegion{boundTL, boundTR, platTL, platTR, 2};
    Trapezoid leftRegion{boundTL, platTL, boundBL, platBL, 3};
    Trapezoid botRegion{platBL, platBR, boundBL, boundBR, 0};
    Trapezoid rightRegion{platTR, boundTR, platBR, boundBR, 1};
    Vector2 point{player.x, player.y};

    // credits:
    // programming: hailey lyn
    // design: hailey lyn
    // coolness: hailey lyn

    if (CheckCollisionRecs(Rectangle{player.x - (player.width / (float)2.0), player.y - (player.height / (float)2.0), player.width, player.height},
                           Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}))
    {
        if (botRegion.isPointIn(point)) // player's top
        {
            player.y = dimensions.y + dimensions.height + player.height / 2.0;
            player.speed_y = 0;
            player.jumpingFrames = 0;
            // cout << "pl top" << endl;
        }
        else if (leftRegion.isPointIn(point)) // player's right
        {
            player.x = dimensions.x - player.width / 2.0;
            player.speed_x = 0;
            player.framesAccelerated = 0;
            player.speed_x_outside = speed_x;
            // cout << "pl right" << endl;
        }
        else if (topRegion.isPointIn(point)) // player's bot
        {
            player.y = dimensions.y + 3.0 - player.height / 2.0;
            player.framesFalling = 0;
            player.speed_y = speed_y - 3.0;
            player.airborne = false;
            player.dashes = player.maxDashes;
            player.speed_x_outside = speed_x;
            player.speed_y_outside = speed_y;
            player.jumpingFrames = 0;
            // cout << "pl bot" << endl;
        }
        else if (rightRegion.isPointIn(point)) // player's left
        {
            player.x = dimensions.x + dimensions.width + player.width / 2.0;
            player.speed_x = 0;
            player.framesAccelerated = 0;
            player.speed_x_outside = speed_x;
            // cout << "pl left" << endl;
        }
        else
        {
            cout << "colliding not in a region - probably clipped into platform" << endl;
        }
    }
}

void Platform::movePlatform()
{
    if (!canMove)
    {
        return;
    }

    if (currentFrame >= periodLength)
    {
        currentFrame -= periodLength;
    }

    int totalPhaseFrames = 0;
    // find the phase it's in
    for (int i = 0; i < (int)movement.size(); i++)
    {
        totalPhaseFrames += movement[i].z;
        if (currentFrame < totalPhaseFrames)
        {
            // add acceleration to speed
            speed_x += movement[i].x;
            speed_y += movement[i].y; // should be positive

            dimensions.x += speed_x;
            dimensions.y -= speed_y; // THIS should be negative
            currentFrame++;
            return;
            ;
        }
    }
}