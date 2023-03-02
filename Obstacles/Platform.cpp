
#include <raylib.h>
#include <iostream>

#include "Platform.h"

void Platform::collision(Player &player)
{
    if (CheckCollisionRecs(Rectangle{player.x - (player.width / (float)2.0), player.y - (player.height / (float)2.0), player.width, player.height},
                           Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height})) // checks if boxes are colliding
    {
        float min = abs(player.y - dimensions.y);
        int minDir = 0; // 0 is player's up, 1 is left, 2 is down, 3 is right

        float left = abs(player.x - dimensions.x);
        if (left < min)
        {
            min = left;
            minDir = 1;
        }

        float down = abs(player.y - (dimensions.y + dimensions.height));
        if (down < min)
        {
            min = down;
            minDir = 2;
        }

        float right = abs(player.x - (dimensions.x + dimensions.width));
        if (right < min)
        {
            min = right;
            minDir = 3;
        }

        switch (minDir)
        {
        case 0: // player's top
            player.y = dimensions.y + dimensions.height + player.height / 2.0;
            player.speed_y = 0;
            player.jumpingFrames = 0;
            break;
        case 1: // player's left
            player.x = dimensions.x - player.width / 2.0;
            player.speed_x = 0;
            player.framesAccelerated = 0;
            player.speed_x_outside = speed_x;
            break;
        case 2: // player's bottom
            player.y = dimensions.y + 3.0 - player.height / 2.0;
            player.framesFalling = 0;
            player.speed_y = speed_y - 3.0;
            player.airborne = false;
            player.dashes = player.maxDashes;
            player.speed_x_outside = speed_x;
            player.speed_y_outside = speed_y;
            player.jumpingFrames = 0;
            break;
        case 3: // player's right
            player.x = dimensions.x + dimensions.width + player.width / 2.0;
            player.speed_x = 0;
            player.framesAccelerated = 0;
            player.speed_x_outside = speed_x;
            break;
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
