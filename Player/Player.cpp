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

    speed_x = speed_x_outside;
    // walk key
    currentMoveSpd = (IsKeyDown(KEY_LEFT_CONTROL)) ? (0.5 * maxMoveSpd) : (maxMoveSpd);

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
            speed_y = 0;

        framesFalling = 0;
        jumpingFrames = 0;

        float dashDistance = currentMoveSpd * (1 + dashingFrames / 12.0); ///////////////////////////////////////////////////////////////

        if (netDir_x == 0 && netDir_y == 0) // if both are pressed or neither pressed, the player is not moving
        {
            if (lastKeyPressed == KEY_W)
            {
                if (dashingFrames != 16)
                {
                    framesAccelerated = 0;
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
                    framesAccelerated = dirFacing * framesToAccelerate;
                    lastKeyPressed = dirFacing == 1 ? KEY_D : KEY_A;
                }
            }
            else if (lastKeyPressed == KEY_S)
            {
                if (dashingFrames != 16)
                {
                    speed_y = -dashDistance;
                    framesAccelerated = 0;
                }
                else
                {
                    speed_x = dirFacing * dashDistance;
                    framesAccelerated = dirFacing * framesToAccelerate;
                }
            }
            else if (lastKeyPressed == KEY_A)
            {
                speed_x = -dashDistance;
                framesAccelerated = -framesToAccelerate;
            }
            else if (lastKeyPressed == KEY_D)
            {
                speed_x = dashDistance;
                framesAccelerated = framesToAccelerate;
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
                framesAccelerated = (int)(framesToAccelerate / sqrt(2));
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
                framesAccelerated = (int)(-framesToAccelerate / sqrt(2));
            }
            else if (lastKeyPressed == 3)
            {
                speed_x = -dashDistance / sqrt(2);
                speed_y = -dashDistance / sqrt(2);
                framesAccelerated = (int)(-framesToAccelerate / sqrt(2));
            }
            else if (lastKeyPressed == 4)
            {
                speed_x = dashDistance / sqrt(2);
                speed_y = -dashDistance / sqrt(2);
                framesAccelerated = (int)(framesToAccelerate / sqrt(2));
            }
        }
        else if (netDir_x == 0 && netDir_y == 1) // straight up
        {
            lastKeyPressed = KEY_W;
            framesAccelerated = 0;
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
            framesAccelerated = 0;
        }
        else if (netDir_x == 1 && netDir_y == 0) // straight right
        {
            speed_x = dashDistance;
            lastKeyPressed = KEY_D;
            framesAccelerated = framesToAccelerate;
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
            framesAccelerated = (int)(framesToAccelerate / sqrt(2));
        }
        else if (netDir_x == 1 && netDir_y == -1) // down right
        {
            speed_x = dashDistance / sqrt(2);
            speed_y = -dashDistance / sqrt(2);
            lastKeyPressed = 4; // quadrant 4
            framesAccelerated = (int)(framesToAccelerate / sqrt(2));
        }
        else if (netDir_x == -1 && netDir_y == 0) // straight left
        {
            speed_x = -dashDistance;
            lastKeyPressed = KEY_A;
            framesAccelerated = -framesToAccelerate;
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
            framesAccelerated = (int)(-framesToAccelerate / sqrt(2));
        }
        else if (netDir_x == -1 && netDir_y == -1) // down left
        {
            speed_x = -dashDistance / sqrt(2);
            speed_y = -dashDistance / sqrt(2);
            lastKeyPressed = 3; // quadrant 3
            framesAccelerated = (int)(-framesToAccelerate / sqrt(2));
        }
        dashingFrames--;
        if (dashingFrames == -1)
        {
            dashing = false;
        }
    }
    else // not dashing
    {
        if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
        {
            if (framesAccelerated != framesToAccelerate)
            {
                framesAccelerated++;
            }
            lastKeyPressed = KEY_D;
        }
        else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
        {
            if (framesAccelerated != -framesToAccelerate)
            {
                framesAccelerated--;
            }
            lastKeyPressed = KEY_A;
        }
        else if (IsKeyDown(KEY_W) == IsKeyDown(KEY_S) && IsKeyDown(KEY_A) == IsKeyDown(KEY_D))
        {
            if (framesAccelerated > 0)
            {
                framesAccelerated--;
            }
            else if (framesAccelerated < 0)
            {
                framesAccelerated++;
            }
        }
        else // W or S are held
        {
            framesAccelerated = 0;
        }
        speed_x += framesAccelerated * currentMoveSpd / framesToAccelerate;
        speed_y += speed_y_outside;
        cout << "sx out " << speed_x_outside << ", sy out " << speed_y_outside << endl;
        cout << "sx " << speed_x << ", sy " << speed_y << endl;
        if (IsKeyPressed(KEY_J))
        {
            if (swordSwingFrames == -1)
            {
                swordSwingFrames = 15;
            }
        }
        if (swordSwingFrames != -1)
        {
            swordSwingFrames --;
        }
    }

    // jump functionality
    if (IsKeyPressed(KEY_SPACE) && !airborne) // pressed jump on ground to start jump
    {
        jumpingFrames = 30;
        airborne = true;
        speed_y += 2.0; // must be the same as initial falling speed in platform.cpp

        if (speed_y == 0 && !dashing)
        {
            speed_y = 6.525;
        }
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

    if (showDashShadows && dashingFrames % 3 == 0)
    {
        dashTrail.insert(dashTrail.begin(), Vector3{x, y, -999});
    }

    x += speed_x;
    y -= speed_y; // positive y is downwards
}