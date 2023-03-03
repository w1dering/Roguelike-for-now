#include <raylib.h>
#include <tgmath.h>
#include <vector>
#include <iostream>

#include "../Weapons/Sword.h"
#include "Player.h"

using namespace std;

void Player::move()
{
    // checks the net direction the player wants to move
    // 1 is right/up
    // 0 is both held or none held
    // -1 is left/down
    int netDir_x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    int netDir_y = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
    if (netDir_x != 0) // if netDir_x is 0, dir facing should stay the same
    {
        dirFacing = netDir_x; // if netDir_x is not 0, dir facing is where you're going
    }

    // walk key
    currentMoveSpd = (IsKeyDown(KEY_LEFT_CONTROL)) ? (0.5 * maxWalkSpeed) : (maxWalkSpeed);

    // dashing
    if (IsKeyPressed(KEY_LEFT_SHIFT) && dashes > 0 && !dashing)
    {
        dashes--;
        showDashShadows = true;
        dashing = true;
        dashingFrames = 16;
    }

    if (dashing)
    {
        if (airborne)
        {
            speed_y = 0;
            speed_x_base = 0;
        }
        framesFalling = 0;
        jumpingFrames = 0;

        float dashDistance = currentMoveSpd * (1 + dashingFrames / 12.0); ///////////////////////////////////////////////////////////////

        if (netDir_x == 0 && netDir_y == 0) // if both are pressed or neither pressed, the player is not moving
        {
            if (lastKeyPressed == KEY_W)
            {
                if (dashingFrames != 16)
                {
                    if (dashingFrames != 0)
                    {
                        speed_y = dashDistance;
                    }
                    else
                    {
                        speed_y = dashDistance / 2.0000; // cuts upwards momentum on last frame of dash - otherwise, dash propels you too far after completion
                    }
                }
                else
                {
                    speed_x = dirFacing * dashDistance;
                    lastKeyPressed = dirFacing == 1 ? KEY_D : KEY_A;
                }
            }
            else if (lastKeyPressed == KEY_S)
            {
                if (dashingFrames != 16)
                {
                    speed_y = -dashDistance;
                }
                else
                {
                    speed_x = dirFacing * dashDistance;
                }
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
                if (dashingFrames != 0)
                {
                    speed_y = dashDistance / sqrt(2);
                }
                else
                {
                    speed_y = dashDistance / 2.0000;
                }
            }
            else if (lastKeyPressed == 2)
            {
                speed_x = -dashDistance / sqrt(2);
                if (dashingFrames != 0)
                {
                    speed_y = dashDistance / sqrt(2);
                }
                else
                {
                    speed_y = dashDistance / 2.0000;
                }
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
        }
        else if (netDir_x == 0 && netDir_y == 1) // straight up
        {
            lastKeyPressed = KEY_W;
            if (dashingFrames != 0)
            {
                speed_y = dashDistance;
            }
            else
            {
                speed_y = dashDistance / 2.0000;
            }
        }
        else if (netDir_x == 0 && netDir_y == -1) // straight down
        {
            speed_y = -dashDistance;
            lastKeyPressed = KEY_S;
        }
        else if (netDir_x == 1 && netDir_y == 0) // straight right
        {
            speed_x = dashDistance;
            lastKeyPressed = KEY_D;
        }
        else if (netDir_x == 1 && netDir_y == 1) // up right
        {
            speed_x = dashDistance / sqrt(2);
            if (dashingFrames != 0)
            {
                speed_y = dashDistance / sqrt(2);
            }
            else
            {
                speed_y = dashDistance / 2.0000;
            }
            lastKeyPressed = 1; // quadrant 1
        }
        else if (netDir_x == 1 && netDir_y == -1) // down right
        {
            speed_x = dashDistance / sqrt(2);
            speed_y = -dashDistance / sqrt(2);
            lastKeyPressed = 4; // quadrant 4
        }
        else if (netDir_x == -1 && netDir_y == 0) // straight left
        {
            speed_x = -dashDistance;
            lastKeyPressed = KEY_A;
        }
        else if (netDir_x == -1 && netDir_y == 1) // up left
        {
            speed_x = -dashDistance / sqrt(2);
            if (dashingFrames != 0)
            {
                speed_y = dashDistance / sqrt(2);
            }
            else
            {
                speed_y = dashDistance / 2.0000;
            }
            lastKeyPressed = 2; // quadrant 2
        }
        else if (netDir_x == -1 && netDir_y == -1) // down left
        {
            speed_x = -dashDistance / sqrt(2);
            speed_y = -dashDistance / sqrt(2);
            lastKeyPressed = 3; // quadrant 3
        }
        dashingFrames--;
        if (dashingFrames == -1)
        {
            dashing = false;
        }
    }
    else // not dashing
    {
        if (speed_x_base > 0 && airborne)
        {
            speed_x_base -= 0.05;
            if (speed_x_base < 0)
            {
                speed_x_base = 0;
            }
        }
        else if (speed_x_base < 0 && airborne)
        {
            speed_x_base += 0.05;
            if (speed_x_base > 0)
            {
                speed_x_base = 0;
            }
        }
        if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
        {
            speed_x += 0.4 * currentMoveSpd;
            if (airborne && speed_x > speed_x_base + currentMoveSpd)
            {
                speed_x -= 0.05 * framesFalling;
                if (speed_x < speed_x_base + currentMoveSpd)
                {
                    speed_x = currentMoveSpd;
                }
            }
            lastKeyPressed = KEY_D;
        }
        else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
        {
            speed_x -= 0.4 * currentMoveSpd;
            if (airborne && speed_x < speed_x_base - currentMoveSpd)
            {
                speed_x += 0.05 * framesFalling;
                if (speed_x > speed_x_base - currentMoveSpd)
                {
                    speed_x = -currentMoveSpd;
                }
            }
            lastKeyPressed = KEY_A;
        }
        else
        {
            if (airborne)
            {
                if (speed_x > 0)
                {
                    speed_x -= 0.05 * framesFalling;
                    if (speed_x < 0)
                    {
                        speed_x = 0;
                    }
                }
                else if (speed_x < 0)
                {
                    speed_x += 0.05 * framesFalling;
                    if (speed_x > 0)
                    {
                        speed_x = 0;
                    }
                }
            }
        }
        if (speed_x > speed_x_base && !airborne)
        {
            speed_x -= 0.2 * currentMoveSpd; // decelerates player if on ground

            if (speed_x < speed_x_base)
            {
                speed_x = speed_x_base;
            }
        }
        else if (speed_x < speed_x_base && !airborne)
        {
            speed_x += 0.2 * currentMoveSpd;
            if (speed_x > speed_x_base)
            {
                speed_x = speed_x_base;
            }
        }

        if (speed_x > currentMoveSpd + speed_x_base) // caps speed
        {
            speed_x = currentMoveSpd + speed_x_base;
        }
        else if (speed_x < -currentMoveSpd + speed_x_base)
        {
            speed_x = -currentMoveSpd + speed_x_base;
        }

        if (IsKeyPressed(KEY_J))
        {
            if (swordSwingFrames == -1)
            {
                swordSwingFrames = 15;
            }
        }
        if (swordSwingFrames != -1)
        {
            swordSwingFrames--;
        }
        // jump functionality
        if (IsKeyPressed(KEY_SPACE) && !airborne && !dashing) // pressed jump on ground to start jump
        {
            jumpingFrames = 30;
            airborne = true;
            // speed_x *= 1.4;
            speed_y *= 2.0;   // the scale of the moving platform's speed on the player: lower number = less momentum transfer
            speed_y += 6.525; // must be the same as initial falling speed in platform.cpp
        }
        else if (IsKeyDown(KEY_SPACE) && jumpingFrames > 0) // holding jump to increase height
        {
            jumpingFrames--;
            speed_y -= 0.015 * (30.0 - jumpingFrames);
        }
        else if (airborne && jumpingFrames > 0)
        {
            speed_y /= 2.5;
            jumpingFrames = 0;
            framesFalling = 0;
        }
        else if (airborne && !dashing)
        {
            // if (speed_y > 0)
            // {
            //     speed_y = 0;
            // }

            speed_y -= 0.05 * framesFalling;
            if (speed_y < terminalVelocity) // less than because terminal velocity is negative
            {
                speed_y = terminalVelocity;
            }
            framesFalling++;
        }
    }

    if (showDashShadows && dashingFrames % 3 == 0)
    {
        dashTrail.insert(dashTrail.begin(), Vector3{x, y, -999});
    }

    x += speed_x;
    y -= speed_y; // positive y is downwards
}