#include <raylib.h>
#include <iostream>

#include "Platform.h"
#include "Trapezoid.h"

void Platform::collision(Player &player)
{
    Vector2 boundTL{dimensions.x - player.width / (float)2.0, dimensions.y - player.height / (float)2.0};
    Vector2 boundTR{dimensions.x + dimensions.width + player.width / (float)2.0, dimensions.y - player.height / (float)2.0};
    Vector2 boundBL{dimensions.x - player.width / (float)2.0, dimensions.y + dimensions.height + player.height / (float)2.0};
    Vector2 boundBR{dimensions.x + dimensions.width + player.width / (float)2.0, dimensions.y + dimensions.height + player.height / (float)2.0};

    Vector2 platTL{dimensions.x, dimensions.y};
    Vector2 platTR{dimensions.x + dimensions.width, dimensions.y};
    Vector2 platBL{dimensions.x, dimensions.y + dimensions.height};
    Vector2 platBR{dimensions.x + dimensions.width, dimensions.y + dimensions.height};

    float vOffset = (speed_y < 0) ? (-speed_y) : 0;

    Trapezoid topRegion{Vector2{boundTL.x, boundTL.y + 2 + vOffset}, Vector2{boundTR.x, boundTR.y + 2 + vOffset},
                        Vector2{platTL.x, platTL.y + 2 + vOffset}, Vector2{platTR.x, platTR.y + 2 + vOffset}, 2};
    Trapezoid leftRegion{Vector2{boundTL.x, boundTL.y + 2 + vOffset}, Vector2{platTL.x, platTL.y + 2 + vOffset}, boundBL, platBL, 3};
    Trapezoid botRegion{platBL, platBR, boundBL, boundBR, 0};
    Trapezoid rightRegion{Vector2{platTR.x, platTR.y + 2 + vOffset}, Vector2{boundTR.x, boundTR.y + 2 + vOffset},
                          platBR, boundBR, 1};
    Vector2 point{player.x, player.y};
    Vector2 platCenter{dimensions.x + dimensions.width / (float)2.0, dimensions.y + dimensions.height / (float)2.0};

    // credits:
    // programming: hailey lyn
    // design: hailey lyn
    // coolness: hailey lynF
    if (CheckCollisionRecs(Rectangle{player.x - (player.width / (float)2.0), player.y - (player.height / (float)2.0), player.width, player.height},
                           Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}))
    {
        if (topRegion.isPointIn(point) || CheckCollisionPointRec(point, Rectangle{boundTL.x, boundTL.y, boundTR.x - boundTL.x,
        3 + vOffset}) || CheckCollisionPointTriangle(point, topRegion.BL, topRegion.BR,
        platCenter)) // player's bot
        {
            player.speed_x_base = 0.0;

            if (spikes[0])
            {
                player.speed_y = 8.0;
                player.hp -= 0.2 * player.maxHp;
                cout << "player's bot spiked" << endl;
                player.dashing = false;
            }
            else
            {
                player.y = dimensions.y - player.height / 2.0 + 0.1;
                player.framesFalling = 0;
                if (!player.dashing)
                {
                    player.speed_y = speed_y;
                    player.speed_x_base = speed_x;
                }
                player.airborne = false;
                player.dashes = player.maxDashes;
                // if (player.speed_x_outside == 0.0)
                // {
                // }
                player.jumpingFrames = 0;
                // cout << "pl bot" << endl;
                player.maxMoveSpd = player.maxWalkSpeed + abs(speed_x);
            }
        }
        else if (botRegion.isPointIn(point) || CheckCollisionPointTriangle(point, platBL, platBR, platCenter)) // player's top
        {
            if (spikes[1])
            {
                player.hp -= 0.2 * player.maxHp;
                player.speed_y = -1.0;
                cout << "player's top spiked" << endl;
                player.dashing = false;
            }
            else
            {
                player.y = dimensions.y + dimensions.height + player.height / 2.0;
                player.speed_y = 0;
                player.jumpingFrames = 0;
            }
            // cout << "pl top" << endl;
        }
        else if (leftRegion.isPointIn(point) || CheckCollisionPointTriangle(point, leftRegion.TR, leftRegion.BR, platCenter)) // player's right
        {
            if (spikes[2])
            {
                player.speed_x = -4.24; // outside??
                player.speed_y = 4.24;
                player.hp -= 0.2 * player.maxHp;
                cout << "player's right spiked" << endl;
                player.dashing = false;
            }
            else
            {
                player.x = dimensions.x - player.width / 2.0;
                player.speed_x = speed_x;
                player.maxMoveSpd = player.maxWalkSpeed + abs(speed_x);
            }
            // cout << "pl right" << endl;
        }
        else if (rightRegion.isPointIn(point) || CheckCollisionPointTriangle(point, rightRegion.TL, rightRegion.TR, platCenter)) // player's left
        {
            if (spikes[3])
            {
                WaitTime(0.2);
                player.speed_x = 4.24;
                player.speed_y = 4.24;
                player.hp -= 0.2 * player.maxHp;
                player.dashing = false;
                cout << "player's left spiked" << endl;
            }
            else
            {
                player.x = dimensions.x + dimensions.width + player.width / 2.0;
                player.speed_x = speed_x;
                player.maxMoveSpd = player.maxWalkSpeed + abs(speed_x);

                // cout << "pl left" << endl;
            }
        }
        else
        {
            cout << "colliding not in a region - probably clipped into platform" << endl;
        }
    }
}

void Platform::movePlatform()
{
    if (!canMove)
    {
        return;
    }

    if (currentFrame >= periodLength)
    {
        currentFrame -= periodLength;
    }

    int totalPhaseFrames = 0;
    // find the phase it's in
    for (int i = 0; i < (int)movement.size(); i++)
    {
        totalPhaseFrames += movement[i].z;
        if (currentFrame < totalPhaseFrames)
        {
            // add acceleration to speed
            speed_x += movement[i].x;
            speed_y += movement[i].y; // should be positive

            dimensions.x += speed_x;
            dimensions.y -= speed_y; // THIS should be negative
            currentFrame++;
            return;
            ;
        }
    }
}