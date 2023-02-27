#include <iostream>
#include <raylib.h>
#include <tgmath.h>
#include <ctime>
#include <iostream>
#include <vector>


#include <Player.cpp>

using namespace std;

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 600;
    double ball_x = 100;
    double ball_y = 100;
    double ball_radius = 15;

    // Player player
    // move below to player.cpp class
    Player player;

    // Platform platform1
    // move below to platform.cpp class (eventually)
    double platform_x = 0;
    double platform_y = 550;
    double platform_w = 800;
    double platform_h = 50;

    InitWindow(screenWidth, screenHeight, "Roguelike for now");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        player.move(ball_x, ball_y, ball_radius);

        // needs to iterate through every platform on the screen
        if (ball_y >= platform_y - ball_radius)
        {
            ball_y = platform_y - ball_radius;
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

        // doesn't let the ball go out of bounds
        if (ball_x >= screenWidth - ball_radius)
            ball_x = screenWidth - ball_radius;
        if (ball_x <= ball_radius)
            ball_x = ball_radius;
        if (ball_y >= screenHeight - ball_radius)
            ball_y = screenHeight - ball_radius;
        if (ball_y <= ball_radius)
            ball_y = ball_radius;

        if (player.dashes > 0)
        {
            DrawCircle(ball_x, ball_y, ball_radius, SKYBLUE); // sky blue ring around player to indicate they have a dash
            DrawCircle(ball_x, ball_y, ball_radius * 0.6, player.playerColor);
        }
        else
        {
            DrawCircle(ball_x, ball_y, ball_radius, player.playerColor);
        }
        DrawRectangle(platform_x, platform_y, platform_w, platform_h, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}