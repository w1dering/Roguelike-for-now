#include <Player.cpp>

class Platform
{
public:
    double platform_w;
    double platform_h;
    double platform_x;
    double platform_y;

    Platform()
    {
    }

    void collision(Player player)
    {
        if (player.y >= platform_y - player.radius)
        {
            player.y = platform_y - player.radius;
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