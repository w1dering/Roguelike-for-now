#include <iostream>
#include <raylib.h>
#include <tgmath.h>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 600;
    double ball_x = 100;
    double ball_y = 100;
    int ball_radius = 15;

    // Player player
    // move below to player.cpp class
    const double moveSpd = 5;
    int lastKeyPressed;
    int dashingFrames = 0;
    int currentMoveSpd = moveSpd;
    bool dashing = false;
    int jumpingFrames = 0;
    bool airborne = true;
    double speed_y = 0;
    const int terminalVelocity = -30;
    int framesFalling = 0;
    double dashes = 1;

    // Platform platform1
    // move below to platform.cpp class (eventually)
    double platform_x = 0;
    double platform_y = 550;
    double platform_w = 800;
    double platform_h = 50;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // walk key
        if (IsKeyDown(KEY_LEFT_CONTROL))
        {
            currentMoveSpd = 0.5 * moveSpd;
        }
        else
        {
            currentMoveSpd = moveSpd;
        }

        // dashing
        if (IsKeyPressed(KEY_LEFT_SHIFT) && dashes > 0)
        {
            dashes--;
            if (dashingFrames == 0)
            {
                dashing = true;
                dashingFrames = 15;
            }
            speed_y = 0;
        }
        if (dashing)
        {
            speed_y = 0;
            framesFalling = 0;
            double dashDistance = currentMoveSpd * (1 + dashingFrames / 5.0);
            if (IsKeyDown(KEY_W))
            {
                if (IsKeyDown(KEY_D))
                {
                    ball_x += dashDistance / sqrt(2);
                    speed_y = dashDistance / sqrt(2);
                    lastKeyPressed = 1;
                }
                else if (IsKeyDown(KEY_A))
                {
                    ball_x -= dashDistance / sqrt(2);
                    speed_y = dashDistance / sqrt(2);
                    lastKeyPressed = 2;
                }
                else if (!IsKeyDown(KEY_S))
                {
                    speed_y = dashDistance;
                    lastKeyPressed = KEY_W;
                }
            }
            else if (IsKeyDown(KEY_S))
            {
                if (IsKeyDown(KEY_D))
                {
                    ball_x += dashDistance / sqrt(2);
                    speed_y = -dashDistance / sqrt(2);
                    lastKeyPressed = 4;
                }
                else if (IsKeyDown(KEY_A))
                {
                    ball_x -= dashDistance / sqrt(2);
                    speed_y = -dashDistance / sqrt(2);
                    lastKeyPressed = 3;
                }
                else if (!IsKeyDown(KEY_W))
                {
                    lastKeyPressed = KEY_S;
                    speed_y = -dashDistance;
                }
            }
            else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
            {
                ball_x += dashDistance;
                lastKeyPressed = KEY_D;
            }
            else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
            {
                ball_x -= dashDistance;
                lastKeyPressed = KEY_A;
            }
            else if (lastKeyPressed == KEY_W)
            {
                speed_y = dashDistance;
            }
            else if (lastKeyPressed == KEY_S)
            {
                speed_y = -dashDistance;
            }
            else if (lastKeyPressed == KEY_A)
            {
                ball_x -= dashDistance;
            }
            else if (lastKeyPressed == KEY_D)
            {
                ball_x += dashDistance;
            }
            else if (lastKeyPressed == 1) // 1 = NE, 2 = NW, 3 = SW, 4 = SE (quadrants)
            {
                ball_x += dashDistance / sqrt(2);
                speed_y = dashDistance / sqrt(2);
            }
            else if (lastKeyPressed == 2)
            {
                ball_x -= dashDistance / sqrt(2);
                speed_y = dashDistance / sqrt(2);
            }
            else if (lastKeyPressed == 3)
            {
                ball_x -= dashDistance / sqrt(2);
                speed_y = -dashDistance / sqrt(2);
            }
            else if (lastKeyPressed == 4)
            {
                ball_x += dashDistance / sqrt(2);
                speed_y = -dashDistance / sqrt(2);
            }
            dashingFrames--;
            if (dashingFrames == 0)
            {
                dashing = false;
            }
        }
        // else // basic WASD movement
        // if (IsKeyDown(KEY_W)) // commented out because gravity disables the use of the W key except for dashing
        // {
        //     if (IsKeyDown(KEY_D))
        //     {
        //         ball_x += currentMoveSpd / sqrt(2);
        //         ball_y -= currentMoveSpd / sqrt(2);
        //     }
        //     else if (IsKeyDown(KEY_A))
        //     {
        //         ball_x -= currentMoveSpd / sqrt(2);
        //         ball_y -= currentMoveSpd / sqrt(2);
        //     }
        //     else if (!IsKeyDown(KEY_S))
        //     {
        //         ball_y -= currentMoveSpd;
        //     }
        // }
        // else if (IsKeyDown(KEY_S))
        // {
        //     if (IsKeyDown(KEY_D))
        //     {
        //         ball_x += currentMoveSpd / sqrt(2);
        //         ball_y += currentMoveSpd / sqrt(2);
        //     }
        //     else if (IsKeyDown(KEY_A))
        //     {
        //         ball_x -= currentMoveSpd / sqrt(2);
        //         ball_y += currentMoveSpd / sqrt(2);
        //     }
        //     else if (!IsKeyDown(KEY_W))
        //     {
        //         ball_y += currentMoveSpd;
        //     }
        // }
        else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
        {
            ball_x += currentMoveSpd; // replace with new var speed_x (eventually)
        }
        else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
        {
            ball_x -= currentMoveSpd;
        }

        // double check ordering of next three if else's

        // doesn't let ball go through walls or platforms

        // jump functionality
        if (IsKeyDown(KEY_SPACE) && (!airborne || jumpingFrames > 0)) // when space is held, they will go upwards if on the ground (!airborne) or they are able to still go up (jumpingFrames > 0)
        {                                                             // add checker for double jump once u code that in
            if (!airborne)
            {
                jumpingFrames = 30;
                airborne = true;
            }
            else
            {
                jumpingFrames--;
            }
            if (speed_y == 0)
            {
                speed_y = 8.8;
            }
            else
            {
                speed_y -= 0.02 * (30.0 - jumpingFrames);
            }
        }
        else if (airborne && jumpingFrames > 0)
        {
            speed_y = 1.5;
            jumpingFrames = 0;
            framesFalling = 0;
        }
        else if (airborne && !dashing)
        {
            // cout << "if else procced" << endl;
            if (speed_y > 0)
            {
                speed_y = 0;
            }
            speed_y -= 0.05 * framesFalling;
            if (speed_y < terminalVelocity) // less than because terminal velocity is negative
            {
                speed_y = terminalVelocity;
            }
            framesFalling++;
        }

        ball_y -= speed_y; // positive y is downwards
        
        // needs to iterate through every platform on the screen
        if (ball_y >= platform_y - ball_radius)
        {
            ball_y = platform_y - ball_radius;
            framesFalling = 0;
            if (speed_y < 0)
            {
                speed_y = 0;
            }
            jumpingFrames = 0;
            airborne = false;
            dashes = 1;
        }
        else
        {
            airborne = true;
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

        DrawCircle(ball_x, ball_y, ball_radius, WHITE);
        DrawRectangle(platform_x, platform_y, platform_w, platform_h, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}