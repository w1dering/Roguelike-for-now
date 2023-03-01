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
    // cout << "platform: " << platform.x << ", " << platform.y << ", " << platform.width << ", " << platform.height << endl;

    if ((CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float)2.0, player.y - player.height / (float)2.0, player.width, player.height},
                            Rectangle{platform.x, platform.y, platform.width, platform.height}) &&
         !CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float)2.0, prevPos.y - player.height / (float)2.0, player.width, player.height},
                             Rectangle{platform.x, platform.y, platform.width, platform.height})) || // normal case
        // special case
        (!CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float)2.0, prevPos.y - player.height / (float)2.0, player.width, player.height},
                             Rectangle{platform.x, platform.y, platform.width, platform.height}) && // previous position is not colliding
         !CheckCollisionRecs(Rectangle{player.x - player.width / (float)2.0, prevPos.y - player.height / (float)2.0, player.width, player.height},
                             Rectangle{platform.x, platform.y, platform.width, platform.height}) && // if prev position continued x dir, would not collide
         !CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float)2.0, player.y - player.height / (float)2.0, player.width, player.height},
                             Rectangle{platform.x, platform.y, platform.width, platform.height}) && // if prev position continued y dir, would not collide
         CheckCollisionRecs(Rectangle{player.x - player.width / (float)2.0, player.y - player.height / (float)2.0, player.width, player.height},
                            Rectangle{platform.x, platform.y, platform.width, platform.height})))
    {
        // player bottom, platform top checker
        if (player.y > prevPos.y)
        {
            player.y = platform.y - player.height / 2.0;
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
            player.y = platform.y + platform.height + player.height / 2.0;
            player.speed_y = 0;
        }
    }
    else if (CheckCollisionRecs(Rectangle{player.x - player.width / (float)2.0, prevPos.y - player.height / (float)2.0, player.width, player.height},
                                Rectangle{platform.x, platform.y, platform.width, platform.height}) &&
             !CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float)2.0, prevPos.y - player.height / (float)2.0, player.width, player.height},
                                 Rectangle{platform.x, platform.y, platform.width, platform.height}))
    {
        // player right, platform left checker
        if (player.x > prevPos.x)
        {
            player.x = platform.x - player.width / 2.0;
            player.speed_x = 0;
        }
        // player left, platform right checker
        else
        {
            player.x = platform.x + platform.width + player.width / 2.0;
            player.speed_x = 0;
        }
    }
}