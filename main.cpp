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
    const int moveSpd = 5;
    int lastKeyPressed;
    int dashingFrames = 0;
    int currentMoveSpd = moveSpd;
    bool dashing = false;

    cout << "Hello World" << endl;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // sprint key
        if (IsKeyDown(KEY_LEFT_CONTROL))
        {
            currentMoveSpd = 1.4 * moveSpd;
        }
        else
        {
            currentMoveSpd = moveSpd;
        }

        // dashing
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            if (dashingFrames == 0)
            {
                dashing = true;
                dashingFrames = 30;
            }
        }
        else if (dashing)
        {
            double dashDistance = currentMoveSpd * (1 + dashingFrames / 10.0);
                if (IsKeyDown(KEY_W))
                {
                    if (IsKeyDown(KEY_D))
                    {
                        ball_x += dashDistance / sqrt(2);
                        ball_y -= dashDistance / sqrt(2);
                        lastKeyPressed = 1;
                    }
                    else if (IsKeyDown(KEY_A))
                    {
                        ball_x -= dashDistance / sqrt(2);
                        ball_y -= dashDistance / sqrt(2);
                        lastKeyPressed = 2;
                    }
                    else if (!IsKeyDown(KEY_S))
                    {
                        ball_y -= dashDistance;
                        lastKeyPressed = KEY_W;
                    }
                }
                else if (IsKeyDown(KEY_S))
                {
                    if (IsKeyDown(KEY_D))
                    {
                        ball_x += dashDistance / sqrt(2);
                        ball_y += dashDistance / sqrt(2);
                        lastKeyPressed = 4;
                    }
                    else if (IsKeyDown(KEY_A))
                    {
                        ball_x -= dashDistance / sqrt(2);
                        ball_y += dashDistance / sqrt(2);
                        lastKeyPressed = 3;
                    }
                    else if (!IsKeyDown(KEY_W))
                    {
                        ball_y += dashDistance;
                        lastKeyPressed = KEY_S;
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
                    ball_y -= dashDistance;
                }
                else if (lastKeyPressed == KEY_S) 
                {
                    ball_y += dashDistance;
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
                    ball_y -= dashDistance / sqrt(2);
                }
                else if (lastKeyPressed == 2)
                {
                    ball_x -= dashDistance / sqrt(2);
                    ball_y -= dashDistance / sqrt(2);
                }
                else if (lastKeyPressed == 3)
                {
                    ball_x -= dashDistance / sqrt(2);
                    ball_y += dashDistance / sqrt(2);
                }
                else if (lastKeyPressed == 4)
                {
                    ball_x += dashDistance / sqrt(2);
                    ball_y += dashDistance / sqrt(2);
                }
                dashingFrames--;
                cout << "dashingFrames = " << dashingFrames << "\ndashDistance = " << dashDistance << endl;
                if (dashingFrames == 0)
                {
                    dashing = false;
                }
        }
        else if (IsKeyDown(KEY_W)) // basic WASD movement
        {
            if (IsKeyDown(KEY_D))
            {
                ball_x += currentMoveSpd / sqrt(2);
                ball_y -= currentMoveSpd / sqrt(2);
            }
            else if (IsKeyDown(KEY_A))
            {
                ball_x -= currentMoveSpd / sqrt(2);
                ball_y -= currentMoveSpd / sqrt(2);
            }
            else if (!IsKeyDown(KEY_S))
            {
                ball_y -= currentMoveSpd;
            }
        }
        else if (IsKeyDown(KEY_S))
        {
            if (IsKeyDown(KEY_D))
            {
                ball_x += currentMoveSpd / sqrt(2);
                ball_y += currentMoveSpd / sqrt(2);
            }
            else if (IsKeyDown(KEY_A))
            {
                ball_x -= currentMoveSpd / sqrt(2);
                ball_y += currentMoveSpd / sqrt(2);
            }
            else if (!IsKeyDown(KEY_W))
            {
                ball_y += currentMoveSpd;
            }
        }
        else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
        {
            ball_x += currentMoveSpd;
        }
        else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
        {
            ball_x -= currentMoveSpd;
        }

        // doesn't let the ball go out of bounds
        if (ball_x >= screenWidth - ball_radius)
            ball_x -= 5;
        if (ball_x == ball_radius)
            ball_x += 5;
        if (ball_y >= screenHeight - ball_radius)
            ball_y -= 5;
        if (ball_y == ball_radius)
            ball_y += 5;

        DrawCircle(ball_x, ball_y, ball_radius, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}