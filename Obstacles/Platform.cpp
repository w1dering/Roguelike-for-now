#include <raylib.h>
#include <iostream>

#include "Platform.h"

void Platform::collision(Player &player)
{
    Vector2 prevPos{player.x - player.speed_x, player.y - -player.speed_y};

    // debugging (will likely need later on)
    // cout << "\n\nprevPos: " << prevPos.x << ", " << prevPos.y << ", " << player.width << ", " << player.height << endl;
    // cout << "prevPos top left: " << prevPos.x - player.width / (float) 2.0 << ", " << player.y - player.height / (float) 2.0 << endl;
    // cout << "\nplayer: " << player.x << ", " << player.y << ", speeds: " << player.speed_x << ", " << player.speed_y << endl;
    // cout << "player top left: " << player.x - player.width / (float) 2.0 << ", " << player.y - player.height / (float) 2.0 << endl;
    // cout << "platform: " << dimensions.x << ", " << dimensions.y << ", " << dimensions.width << ", " << dimensions.height << endl;

    if ((CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float)2.0, player.y - player.height / (float)2.0, player.width, player.height},
                            Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}) &&
         !CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float)2.0, prevPos.y - player.height / (float)2.0, player.width, player.height},
                             Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height})) || // normal case
        // special case
        (!CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float)2.0, prevPos.y - player.height / (float)2.0, player.width, player.height},
                             Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}) && // previous position is not colliding
         !CheckCollisionRecs(Rectangle{player.x - player.width / (float)2.0, prevPos.y - player.height / (float)2.0, player.width, player.height},
                             Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}) && // if prev position continued x dir, would not collide
         !CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float)2.0, player.y - player.height / (float)2.0, player.width, player.height},
                             Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}) && // if prev position continued y dir, would not collide
         CheckCollisionRecs(Rectangle{player.x - player.width / (float)2.0, player.y - player.height / (float)2.0, player.width, player.height},
                            Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height})))
    {
        // player bottom, platform top checker
        if (player.y > prevPos.y)
        {
            player.y = dimensions.y - player.height / 2.0;
            player.framesFalling = 0;
            player.speed_y = -2; // to ensure collision still occurs, as the box needs to be moving to check
            player.jumpingFrames = 0;
            player.airborne = false;
            player.dashes = player.maxDashes;
            // cout << "player bottom collide" << endl;
        }
        // player top, platform bottom checker
        else
        {
            player.y = dimensions.y + dimensions.height + player.height / 2.0;
            player.speed_y = 0;
            player.jumpingFrames = 0;
        }
        player.speed_x_outside = speed_x;
        player.speed_y_outside = speed_y;
    }
    else if (CheckCollisionRecs(Rectangle{player.x - player.width / (float)2.0, prevPos.y - player.height / (float)2.0, player.width, player.height},
                                Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}) &&
             !CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float)2.0, prevPos.y - player.height / (float)2.0, player.width, player.height},
                                 Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}))
    {
        // player right, platform left checker
        if (player.x > prevPos.x)
        {
            player.x = dimensions.x - player.width / 2.0;
        }
        // player left, platform right checker
        else
        {
            player.x = dimensions.x + dimensions.width + player.width / 2.0;
        }
        player.speed_x = 0;
        player.framesAccelerated = 0;
        player.speed_x_outside = speed_x;
        player.speed_y_outside = speed_y;
    }
    else
    {
        player.speed_x_outside = 0;
        player.speed_y_outside = 0;
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
            return;;
        }
    }
}