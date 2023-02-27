#include <raylib.h>
#include <tgmath.h>
#include <vector>
#include <Particle.cpp>

using namespace std;

class Player
{
public:
    double radius;
    double x;
    double y;
    double moveSpd = 5;
    int lastKeyPressed;
    int dashingFrames = 0;
    int currentMoveSpd = moveSpd;
    bool dashing = false;
    int jumpingFrames = 0;
    bool airborne = true;
    double speed_y = 0;
    const int terminalVelocity = -30;
    int framesFalling = 0;
    int dashes = 1;
    int maxDashes = 1;
    Color playerColor = WHITE;
    std::vector<Particle> particles;

    Player() // should probably have some stuff in here but idk what
    {
    }

    void move(double &x, double &y, double &ball_radius)
    {
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
                    x += dashDistance / sqrt(2);
                    speed_y = dashDistance / sqrt(2);
                    lastKeyPressed = 1;
                }
                else if (IsKeyDown(KEY_A))
                {
                    x -= dashDistance / sqrt(2);
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
                    x += dashDistance / sqrt(2);
                    speed_y = -dashDistance / sqrt(2);
                    lastKeyPressed = 4;
                }
                else if (IsKeyDown(KEY_A))
                {
                    x -= dashDistance / sqrt(2);
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
                x += dashDistance;
                lastKeyPressed = KEY_D;
            }
            else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
            {
                x -= dashDistance;
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
                x -= dashDistance;
            }
            else if (lastKeyPressed == KEY_D)
            {
                x += dashDistance;
            }
            else if (lastKeyPressed == 1) // 1 = NE, 2 = NW, 3 = SW, 4 = SE (quadrants)
            {
                x += dashDistance / sqrt(2);
                speed_y = dashDistance / sqrt(2);
            }
            else if (lastKeyPressed == 2)
            {
                x -= dashDistance / sqrt(2);
                speed_y = dashDistance / sqrt(2);
            }
            else if (lastKeyPressed == 3)
            {
                x -= dashDistance / sqrt(2);
                speed_y = -dashDistance / sqrt(2);
            }
            else if (lastKeyPressed == 4)
            {
                x += dashDistance / sqrt(2);
                speed_y = -dashDistance / sqrt(2);
            }
            dashingFrames--;
            if (dashingFrames == 0)
            {
                dashing = false;
            }
        }
        else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
        {
            x += currentMoveSpd; // replace with new var speed_x (eventually)
        }
        else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
        {
            x -= currentMoveSpd;
        }

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

        y -= speed_y; // positive y is downwards
    }
};