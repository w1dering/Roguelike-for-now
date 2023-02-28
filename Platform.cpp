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
        // player bottom, platform top checker
        cout << "player: " << player.x << ", " << player.y << endl;
        cout << "platform: " << platform.x << ", " << platform.y << ", " << platform.width << ", " << platform.height << endl;
        if (player.hitbox[2][0].y >= platform.y && 
            player.hitbox[2][0].y <= platform.y + platform.height &&
            player.hitbox[0][2].x >= platform.x &&
            player.hitbox[0][0].x <= platform.x + platform.width)
        {
            player.y = platform.y - player.height / 2.0 + 1;
            player.framesFalling = 0;
            if (player.speed_y < 0)
            {
                player.speed_y = 0;
            }
            player.jumpingFrames = 0;
            player.airborne = false;
            player.dashes = player.maxDashes;
            cout << "player bottom collide" << endl;
        }
        else if (player.y - player.height / 2.0 == platform.y + platform.height && 
                player.x + player.width / 2.0 != platform.x && 
                player.x - player.width / 2.0 != platform.x + platform.width && 
                (CheckCollisionPointRec(player.hitbox[0][0], platform) || // player top, platform bottom collision
                CheckCollisionPointRec(player.hitbox[0][1], platform) || CheckCollisionPointRec(player.hitbox[0][2], platform)))
        {
            player.y = platform.y + platform.height + player.height / 2.0;
            if (player.speed_y > 0)
            {
                player.speed_y = 0;
            }
        }
        else if (player.x - player.width / 2.0 == platform.x && player.y + player.height / 2.0 != platform.y && player.y - player.height / 2.0 != platform.y + platform.height && (CheckCollisionPointRec(player.hitbox[0][0], platform) || // player left, platform right collision
                                                                                                                                                                                   CheckCollisionPointRec(player.hitbox[1][0], platform) || CheckCollisionPointRec(player.hitbox[2][0], platform)))
        {
            player.x = platform.x + platform.width + player.width / 2.0;
            player.speed_x = 0;
        }
        else if (player.x + player.width / 2.0 == platform.x + platform.width && player.y + player.height / 2.0 != platform.y && player.y - player.height / 2.0 != platform.y + platform.height && (CheckCollisionPointRec(player.hitbox[0][2], platform) || // player right, platform left collision
                                                                                                                                                                                                    CheckCollisionPointRec(player.hitbox[1][2], platform) || CheckCollisionPointRec(player.hitbox[2][2], platform)))
        {
            player.x = platform.x - player.width / 2.0;
            player.speed_x = 0;
        }
        else
        {
            cout << "player is airborne" << endl;
        }
    }
};