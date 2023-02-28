#include <raylib.h>
#include <tgmath.h>
#include <vector>
#include <iostream>
#include <Weapons/Sword.cpp>

using namespace std;

class Player
{
public:
    // player dimensions
    float x;
    float y;
    float width = 30;
    float height = 30;

    // player stats
    Color playerColor = WHITE;
    int hp = 100;
    int maxHp = 100;

    // player movement
    float maxMoveSpd = 5;
    float speed_x = 0;
    float speed_y = 0;
    const float terminalVelocity = -10; // max falling speed of player
    float currentMoveSpd;
    int framesFalling = 0;

    // player jumping
    int jumpingFrames = 0;
    bool airborne = true;

    // player dashing
    int lastKeyPressed; // used to determine dash direction if player is mid-dash and lets go of controls
    int dirFacing = 1;  // 1 is right, -1 is left
    int dashingFrames = -1;
    bool dashing = false;
    int dashes = 1;
    int maxDashes = 1;

    // player dash trail
    vector<Vector3> dashTrail;
    bool showDashShadows = false;

    // player hitbox vectors
    Vector2 hitbox[3][3];

    // player weaponry
    int swordSwingFrames = 0;

    Player() // should probably have some stuff in here but idk what
    {
    }

    void move(float &x, float &y)
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

        speed_x = 0;
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
                speed_x = dirFacing * dashDistance;
            }
            else if (netDir_x == 0 && netDir_y == 1) // straight up
            {
                speed_y = dashDistance;
                lastKeyPressed = KEY_W;
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
                speed_y = dashDistance / sqrt(2);
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
                speed_y = dashDistance / sqrt(2);
                lastKeyPressed = 2; // quadrant 2
            }
            else if (netDir_x == -1 && netDir_y == -1) // down left
            {
                speed_x = -dashDistance / sqrt(2);
                speed_y = -dashDistance / sqrt(2);
                lastKeyPressed = 3; // quadrant 3
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
        else
        {
            if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
            {
                speed_x = currentMoveSpd;
                lastKeyPressed = KEY_D;
            }
            else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
            {
                speed_x = -currentMoveSpd;
                lastKeyPressed = KEY_A;
            }
            else if (IsKeyDown(KEY_W) == IsKeyDown(KEY_S) && IsKeyDown(KEY_A) == IsKeyDown(KEY_D))
            {
                speed_x = 0;
            }

            if (IsKeyPressed(KEY_J))
            {
                if (swordSwingFrames == -1)
                {
                    swordSwingFrames = 15;
                }
                else
                {
                    swordSwingFrames--;
                }
            }
        }

        // jump functionality
        if (IsKeyPressed(KEY_SPACE) && !airborne) // when space is held, they will go upwards if on the ground (!airborne) or they are able to still go up (jumpingFrames > 0)
        {
            jumpingFrames = 30;
            airborne = true;
            speed_y += 2.0; // must be the same as initial falling speed in platform.cpp

            if (speed_y == 0 && !dashing)
            {
                speed_y = 6.525;
            }
        }
        else if (IsKeyDown(KEY_SPACE) && jumpingFrames > 0)
        {
            jumpingFrames--;
            speed_y -= 0.015 * (30.0 - jumpingFrames);
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
    }
};