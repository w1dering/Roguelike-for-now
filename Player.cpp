#include <raylib.h>
#include <tgmath.h>
#include <vector>
#include <Particle.cpp>
#include <iostream>

using namespace std;

class Player
{
public:
    float width = 30;
    float height = 30;
    float x;
    float y;
    float moveSpd = 5;
    int lastKeyPressed;
    int dirFacing = 1;
    int dashingFrames = -1;
    int currentMoveSpd = moveSpd;
    bool dashing = false;
    int jumpingFrames = 0;
    bool airborne = true;
    float speed_x = 0;
    float speed_y = 0;
    const float terminalVelocity = -12.5;
    int framesFalling = 0;
    int dashes = 1;
    int maxDashes = 1;
    Color playerColor = WHITE;
    int hp = 100;
    int maxHp = 100;

    // coords of dash shadows
    vector<Vector3> dashTrail;
    bool showDashShadows = false;

    // Hitbox vectors
    Vector2 hitbox[3][3];

    Player() // should probably have some stuff in here but idk what
    {
    }

    void move(float &x, float &y)
    {
        speed_x = 0;
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
            if (dashingFrames == -1)
            {
                dashing = true;
                dashingFrames = 16;
            }
            if (airborne)
                speed_y = 0;
            showDashShadows = true;
        }

        if (dashing)
        {
            if (airborne)
                speed_y = 0;
            // if (!airborne)
            // {
            //     speed_y = 1.5; // must be the same as initial falling speed in Platform.cpp
            // }
            framesFalling = 0;
            jumpingFrames = 0;
            float dashDistance = currentMoveSpd * (1 + dashingFrames / 12.0); ///////////////////////////////////////////////////////////////
            if (((IsKeyDown(KEY_W) && IsKeyDown(KEY_S)) || (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))) &&
                ((IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) || (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))))
            {
                if (dirFacing == 1)
                {
                    speed_x = dashDistance;
                }
                else if (dirFacing == 0)
                {
                    speed_x = -dashDistance;
                }
            }
            else if (IsKeyDown(KEY_W))
            {
                if (IsKeyDown(KEY_D))
                {
                    if (!IsKeyDown(KEY_S))
                    {
                        speed_y = dashDistance / sqrt(2);
                        if (dirFacing == 1)
                        {
                            speed_x = dashDistance / sqrt(2);
                            lastKeyPressed = 1;
                        }
                        else
                        {
                            speed_x = -dashDistance / sqrt(2);
                        }
                    }
                    else
                    {
                        speed_x = dashDistance;
                        lastKeyPressed = KEY_D;
                    }
                    if (!IsKeyDown(KEY_A))
                    {

                        dirFacing = 1;
                    }
                }
                else if (IsKeyDown(KEY_A))
                {
                    if (!IsKeyDown(KEY_S))
                    {
                        speed_y = dashDistance / sqrt(2);
                        if (dirFacing == 0)
                        {
                            speed_x = -dashDistance / sqrt(2);
                            lastKeyPressed = 2;
                        }
                        else
                        {
                            speed_x = dashDistance / sqrt(2);
                        }
                    }
                    else
                    {
                        speed_x = -dashDistance;
                        lastKeyPressed = KEY_A;
                    }
                    if (!IsKeyDown(KEY_D))
                    {
                        dirFacing = 0;
                    }
                }
                else if (!IsKeyDown(KEY_S))
                {
                    speed_y = dashDistance;
                    lastKeyPressed = KEY_W;
                }
            }
            else if (IsKeyDown(KEY_S))
            {
                cout << "key s procced" << endl;
                if (IsKeyDown(KEY_D))
                {
                    if (!IsKeyDown(KEY_W))
                    {
                        speed_y = -dashDistance / sqrt(2);
                        if (dirFacing == 1)
                        {
                            speed_x = dashDistance / sqrt(2);
                            lastKeyPressed = 4;
                        }
                        else
                        {
                            speed_x = -dashDistance / sqrt(2);
                        }
                    }
                    else
                    {
                        speed_x = dashDistance;
                        lastKeyPressed = KEY_D;
                    }
                    if (!IsKeyDown(KEY_A))
                    {

                        dirFacing = 1;
                    }
                }
                else if (IsKeyDown(KEY_A))
                {
                    if (!IsKeyDown(KEY_W))
                    {
                        speed_y = -dashDistance / sqrt(2);
                        if (dirFacing == 0)
                        {
                            speed_x = -dashDistance / sqrt(2);
                            lastKeyPressed = 3;
                        }
                        else
                        {
                            speed_x = dashDistance / sqrt(2);
                        }
                    }
                    else
                    {
                        speed_x = -dashDistance;
                        lastKeyPressed = KEY_A;
                    }
                    if (!IsKeyDown(KEY_D))
                    {
                        dirFacing = 0;
                    }
                }
                else if (!IsKeyDown(KEY_W))
                {
                    if (!airborne)
                    {
                        if (dirFacing == 1)
                        {
                            speed_x = dashDistance;
                        }
                        else
                        {
                            speed_x = -dashDistance;
                        }
                    }
                    else
                    {

                        lastKeyPressed = KEY_S;
                        speed_y = -dashDistance;
                    }
                }
            }
            else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
            {
                speed_x = dashDistance;
                dirFacing = 1;
            }
            else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
            {
                speed_x = -dashDistance;
                dirFacing = 0;
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
                speed_x = -dashDistance;
            }
            else if (lastKeyPressed == KEY_D)
            {
                speed_x = dashDistance;
            }
            else if (lastKeyPressed == 1) // 1 = NE, 2 = NW, 3 = SW, 4 = SE (quadrants)
            {
                speed_x = dashDistance / sqrt(2);
                speed_y = dashDistance / sqrt(2);
            }
            else if (lastKeyPressed == 2)
            {
                speed_x = -dashDistance / sqrt(2);
                speed_y = dashDistance / sqrt(2);
            }
            else if (lastKeyPressed == 3)
            {
                speed_x = -dashDistance / sqrt(2);
                speed_y = -dashDistance / sqrt(2);
            }
            else if (lastKeyPressed == 4)
            {
                speed_x = dashDistance / sqrt(2);
                speed_y = -dashDistance / sqrt(2);
            }
            dashingFrames--;
            if (dashingFrames == -1)
            {
                dashing = false;
            }
        }
        else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
        {
            speed_x = currentMoveSpd; // replace with new var speed_x (eventually)
            lastKeyPressed = KEY_D;
            dirFacing = 1;
        }
        else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
        {
            speed_x = -currentMoveSpd;
            lastKeyPressed = KEY_A;
            dirFacing = 0;
        }
        else if (((IsKeyDown(KEY_W) && IsKeyDown(KEY_S)) || (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))) &&
                 ((IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) || (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))))
        {
            speed_x = 0;
        }

        // jump functionality
        if (IsKeyDown(KEY_SPACE) && (!airborne || jumpingFrames > 0)) // when space is held, they will go upwards if on the ground (!airborne) or they are able to still go up (jumpingFrames > 0)
        {
            if (!airborne)
            {
                jumpingFrames = 30;
                airborne = true;
                speed_y += 2.0; // must be the same as initial falling speed in platform.cpp
            }
            else
            {
                jumpingFrames--;
            }
            if (speed_y == 0 && !dashing)
            {
                speed_y = 6.525;
            }
            else
            {
                speed_y -= 0.015 * (30.0 - jumpingFrames);
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

        if (showDashShadows && dashingFrames % 3 == 0)
        {
            dashTrail.insert(dashTrail.begin(), Vector3{x, y, -999});
        }

        x += speed_x;
        y -= speed_y; // positive y is downwards

        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                hitbox[r][c].x = x + (width / 2.0) * (c - 1);
                hitbox[r][c].y = y + (height / 2.0) * (r - 1);
            }
        }
    }
};