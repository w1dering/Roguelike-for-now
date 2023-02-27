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

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    // Player player
    // move below to player.cpp class
    Player player;
    player.x = 100;
    player.y = 100;
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

        player.move(player.x, player.y, player.radius);
        ground.collision(player);

        // doesn't let the ball go out of bounds
        if (player.x >= screenWidth - player.radius)
            player.x = screenWidth - player.radius;
        if (player.x <= player.radius)
            player.x = player.radius;
        if (player.y >= screenHeight - player.radius)
            player.y = screenHeight - player.radius;
        if (player.y <= player.radius)
            player.y = player.radius;

        if (player.dashes > 0)
        {
            DrawCircle(player.x, player.y, player.radius, SKYBLUE); // sky blue ring around player to indicate they have a dash
            DrawCircle(player.x, player.y, player.radius * 0.6, player.playerColor);
        }
        else
        {
            DrawCircle(player.x, player.y, player.radius, player.playerColor);
        }
        DrawRectangle(ground.platform_x, ground.platform_y, ground.platform_w, ground.platform_h, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}