#include <iostream>
#include <raylib.h>
#include <tgmath.h>
#include <ctime>
#include <iostream>
#include <vector>


#include <Player.cpp>
#include <Platform.cpp>

using namespace std;

int main()
{

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    // Player player
    // move below to player.cpp class
    Player player;
    player.ball_x = 100;
    player.ball_y = 100;
    player.radius = 15;

    // Platform platform1
    // move below to platform.cpp class (eventually)
    Platform ground;
    ground.platform_w = screenWidth;
    ground.platform_h = 50;
    ground.platform_x = 0;
    ground.platform_y = screenHeight - ground.platform_h;

    InitWindow(screenWidth, screenHeight, "Roguelike for now");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        player.move(player.ball_x, player.ball_y, player.radius);

        // doesn't let the ball go out of bounds
        if (player.ball_x >= screenWidth - player.radius)
            player.ball_x = screenWidth - player.radius;
        if (player.ball_x <= player.radius)
            player.ball_x = player.radius;
        if (player.ball_y >= screenHeight - player.radius)
            player.ball_y = screenHeight - player.radius;
        if (player.ball_y <= player.radius)
            player.ball_y = player.radius;

        if (player.dashes > 0)
        {
            DrawCircle(player.ball_x, player.ball_y, player.radius, SKYBLUE); // sky blue ring around player to indicate they have a dash
            DrawCircle(player.ball_x, player.ball_y, player.radius * 0.6, player.playerColor);
        }
        else
        {
            DrawCircle(player.ball_x, player.ball_y, player.radius, player.playerColor);
        }
        DrawRectangle(ground.platform_x, ground.platform_y, ground.platform_w, ground.platform_h, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}