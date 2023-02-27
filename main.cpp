#include <iostream>
#include <raylib.h>
#include <tgmath.h>
#include <ctime>
#include <iostream>
#include <vector>

#include <Platform.cpp>

using namespace std;

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 600;

    // Player player
    // move below to player.cpp class
    Player player;
    player.x = 100;
    player.y = 100;

    // Platform platform1
    // move below to platform.cpp class (eventually)
    Platform ground(0, screenHeight - 50, screenWidth + 50, 50);

    InitWindow(screenWidth, screenHeight, "Roguelike for now");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        player.move(player.x, player.y);
        ground.collision(player);

        // doesn't let the ball go out of bounds
        if (player.x >= screenWidth - player.width / 2.0)
            player.x = screenWidth - player.width / 2.0;
        if (player.x <= player.width / 2.0)
            player.x = player.width / 2.0;
        if (player.y >= screenHeight - player.height / 2.0)
            player.y = screenHeight - player.height / 2.0;
        if (player.y <= player.height / 2.0)
            player.y = player.height / 2.0;

        if (player.showDashShadows == true)
        {
            if (player.dashingFrames % 3 == 0 && player.dashShadows[0].z < 0)
            {
                player.dashShadows[player.dashingFrames / 3].z = 180;
            }

            for (int i = 5; i >= 0; i--)
            {
                if (player.dashShadows[i].z > 0)
                {
                    Color shadowColor{102, 191, 255, (unsigned char) player.dashShadows[i].z};
                    DrawCircle(player.dashShadows[i].x, player.dashShadows[i].y, player.width / 2.0, shadowColor);
                    player.dashShadows[i].z -= 5;
                    if (i == 0 && player.dashShadows[0].z < 0 &&
                        player.dashShadows[1].z < 0 &&
                        player.dashShadows[2].z < 0 &&
                        player.dashShadows[3].z < 0 &&
                        player.dashShadows[4].z < 0 &&
                        player.dashShadows[5].z < 0)
                    {
                        player.showDashShadows = false;
                    }
                }
            }
        }

        DrawRectangle(ground.platform.x, ground.platform.y, ground.platform.width, ground.platform.height, WHITE); // draw platform

        if (player.dashes > 0)
        {
            DrawCircle(player.x, player.y, player.width / 2.0, SKYBLUE); // sky blue ring around player to indicate they have a dash
            DrawCircle(player.x, player.y, player.width / 2.0 * 0.6, player.playerColor);
        }
        else
        {
            DrawCircle(player.x, player.y, player.width / 2.0, player.playerColor);
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}