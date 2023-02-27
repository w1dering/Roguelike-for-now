#include <Player.cpp>
#include <raylib.h>

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
        
        if (CheckCollisionPointRec(player.hitbox[2][0], platform) ||
        CheckCollisionPointRec(player.hitbox[2][1], platform) ||
        CheckCollisionPointRec(player.hitbox[2][2], platform))
        {
            player.y = platform.y - player.height / 2.0;
            player.framesFalling = 0;
            if (player.speed_y < 0)
            {
                player.speed_y = 0;
            }
            player.jumpingFrames = 0;
            player.airborne = false;
            player.dashes = player.maxDashes;
        }
        else
        {
            player.airborne = true;
        }
    }
};