#include <Player.cpp>
#include <raylib.h>
#include <iostream>

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

    void collision(Player &player)
    {
        Vector2 prevPos{player.x - player.speed_x, player.y - -player.speed_y};
        // cout << "\n\nprevPos: " << prevPos.x << ", " << prevPos.y << ", " << player.width << ", " << player.height << endl;
        // cout << "prevPos top left: " << prevPos.x - player.width / (float) 2.0 << ", " << player.y - player.height / (float) 2.0 << endl;
        // cout << "\nplayer: " << player.x << ", " << player.y << ", speeds: " << player.speed_x << ", " << player.speed_y << endl;
        // cout << "player top left: " << player.x - player.width / (float) 2.0 << ", " << player.y - player.height / (float) 2.0 << endl;
        // cout << "platform: " << platform.x << ", " << platform.y << ", " << platform.width << ", " << platform.height << endl;
        if ( CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float) 2.0, player.y - player.height / (float) 2.0, player.width, player.height},
                                Rectangle{platform.x, platform.y, platform.width, platform.height}) &&
            !CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float) 2.0, prevPos.y - player.height / (float) 2.0, player.width, player.height},
                                Rectangle{platform.x, platform.y, platform.width, platform.height}))
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
                cout << "player top collide" << endl;
            }
        }
        // player left, platform right checker
        else if (CheckCollisionRecs(Rectangle{player.x - player.width / (float) 2.0, prevPos.y - player.height / (float) 2.0, player.width, player.height},
                               Rectangle{platform.x, platform.y, platform.width, platform.height}) &&
            !CheckCollisionRecs(Rectangle{prevPos.x - player.width / (float) 2.0, prevPos.y - player.height / (float) 2.0, player.width, player.height},
                                Rectangle{platform.x, platform.y, platform.width, platform.height}))
        {
            // player right, platform left checker
            if (player.x > prevPos.x)
            {
                player.x = platform.x - player.width / 2.0;
                player.speed_x = 0;
                cout << "player right collide" << endl;
            }
            else
            {
                player.x = platform.x + platform.width + player.width / 2.0;
                player.speed_x = 0;
                cout << "player left collide" << endl;
            }
        }
    }
};