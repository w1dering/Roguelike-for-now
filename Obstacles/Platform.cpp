
#include <raylib.h>
#include <iostream>

#include "Platform.h"

void Platform::collision(Player &player)
{
    // x and y of previous position
    Vector2 prevPos{player.prev_x, player.prev_y};
    Vector2 prevPlatPos{dimensions.x - speed_x, dimensions.y - -speed_y};

    // declares top left positions of current and previous position
    float prevPosTLX = prevPos.x - player.width / (float)2.0;
    float prevPosTLY = prevPos.y - player.height / (float)2.0;
    float playerTLX = player.x - player.width / (float)2.0;
    float playerTLY = player.y - player.height / (float)2.0;

    bool hCol = false;
    bool vCol = false;
    bool hPlatCol = false; // stores if it's a collision of platform moving into player, rather than player moving into platform
    bool vPlatCol = false;
    int dirOfCol = 0; // -1 is negative coord dir (down, left), 1 is positive coord dir (up, right) from player

    Vector2 diffDistances{player.x - player.prev_x, player.prev_y - player.y};

    if (CheckCollisionRecs(Rectangle{playerTLX, playerTLY, player.width, player.height}, dimensions)) // checks if hitboxes are colliding
    {
        cout << "\n\n\n\nprevPos: " << prevPosTLX << ", " << prevPosTLY << ", spd: " << diffDistances.x << ", " << diffDistances.y << endl;
        cout << "prevPos center: " << prevPos.x << ", " << prevPos.y << endl;
        cout << "prevPlatPos: " << prevPlatPos.x << ", " << prevPlatPos.y << ", " << dimensions.width << ", " << dimensions.height << endl;
        cout << "speed: " << speed_x << ", " << speed_y << endl;

        cout << "\ncurrent player pos: " << playerTLX << ", " << playerTLY << ", " << player.speed_x << ", " << player.speed_y << endl;
        cout << "current plat pos: " << dimensions.x << ", " << dimensions.y << endl;

        for (float i = 0.1; i < 1.1; i += 0.1) // this makes 10 separate "subframes" - whichever direction collides first will be the direction of rebound
        {
            cout << "\n\ni: " << i << endl;
            if (CheckCollisionRecs(Rectangle{prevPosTLX, prevPosTLY, player.width, player.height}, Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}))
            {
                cout << "previous player collides with current platform" << endl;
            }
            cout << "i x * " << (i * diffDistances.x) << endl;
            cout << "i y * " << (i * diffDistances.y) << endl;
            cout << "rec x: " << prevPosTLX + (i * diffDistances.x) << endl;
            cout << "rec y: " << prevPosTLY << endl;
            cout << "rec w: " << player.width << endl;
            cout << "rec h: " << player.height << "\n" << endl;
            cout << "dim x: " << dimensions.x << endl;
            cout << "dim y: " << dimensions.y << endl;
            cout << "dim w: " << dimensions.width << endl;
            cout << "dim h: " << dimensions.height << endl;

            cout << "\nhCol: " << hCol << endl;
            cout << "vCol: " << vCol << endl;
            cout << "hPlatCol: " << hPlatCol << endl;
            cout << "vPlatCol: " << vPlatCol << endl;

            cout << "check colX" << CheckCollisionRecs(Rectangle{prevPosTLX + (i * diffDistances.x), prevPosTLY, player.width, player.height}, Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}) << endl;

            // this will check for horizontal collisions from previous position by ONLY moving in the x direction -- if true, it's a horizontal collision
            if (canMove && CheckCollisionRecs(Rectangle{prevPlatPos.x + (i * speed_x), prevPlatPos.y, dimensions.width, dimensions.height},
                                                   Rectangle{playerTLX, playerTLY, player.width, player.height}))
            {
                hPlatCol = true;
                dirOfCol = player.x < (prevPlatPos.x + (dimensions.width / 2.0)) ? 1 : -1;
                cout << "hPlatCol, dir is " << dirOfCol << " on i " << i << endl;
            }
            if (CheckCollisionRecs(Rectangle{prevPosTLX + (i * diffDistances.x), prevPosTLY, player.width, player.height},
                                   Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}))
            {
                hCol = true;
                dirOfCol = prevPos.x < (dimensions.x + (dimensions.width / 2.0)) ? 1 : -1; // was the x value of the previous player center to the LEFT of the platform's center?
                // if so, dir of collision is player's right, rebound should be left
                cout << "hCol, dir is " << dirOfCol << " on i " << i << endl;
            }

            cout << "check col Y" << CheckCollisionRecs(Rectangle{prevPosTLX, prevPosTLY - (i * diffDistances.y), player.width, player.height}, 
            Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}) << endl;

            // checking vertical collisions
            
            if (canMove && CheckCollisionRecs(Rectangle{prevPlatPos.x, prevPlatPos.y - (i * speed_y), dimensions.width, dimensions.height},
                                                   Rectangle{playerTLX, playerTLY, player.width, player.height}))
            {
                vPlatCol = true;
                dirOfCol = player.y > (prevPlatPos.y + (dimensions.height / 2.0)) ? 1 : -1;
                cout << "vPlatCol, dir is " << dirOfCol << " on i " << i << endl;
            }
            else if (CheckCollisionRecs(Rectangle{prevPosTLX, prevPosTLY - (i * diffDistances.y), player.width, player.height},
                                   Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height}))
            {
                vCol = true;
                dirOfCol = prevPos.y > (dimensions.y + (dimensions.height / 2.0)) ? 1 : -1;
                // player's prevPos > dimensions center = player's prev pos is BELOW
                // collision would be player's top, so 1
                cout << "vCol, dir is " << dirOfCol << " on i " << i << endl;
            }

            if (i == 1.0)
            {
                vCol = true;
            }

            if ((hCol || vCol) || (hPlatCol || vPlatCol))
            {
                if (hCol && vCol)
                {
                    hCol = false; // prioritizes vertical collisions
                                  // hPlatCol = false;
                    cout << "overruled--------------------------------------" << endl;
                }
                else if (hPlatCol && vPlatCol)
                {
                    hPlatCol = false;
                    // hCol = false;
                    cout << "overruled--------------------------------------" << endl;
                }
                cout << "broken" << endl;
                break;
            }
        }
        diffDistances.x = speed_x;

        if (vCol || vPlatCol)
        {
            if (dirOfCol > 0) // player's top, pushes down
            {
                player.y = dimensions.y + dimensions.height + player.height / 2.0;
                player.speed_y = 0;
                cout << "player's top collision" << endl;
            }
            else // player's bottom, pushes up
            {
                player.y = dimensions.y + 3.0 - player.height / 2.0;
                player.framesFalling = 0;
                player.speed_y = speed_y - 3.0;
                player.airborne = false;
                player.dashes = player.maxDashes;
                player.speed_x_outside = speed_x;
                player.speed_y_outside = speed_y;
                cout << "player's bottom collision" << endl;
            }
            player.jumpingFrames = 0;
        }
        else if (hCol || hPlatCol)
        {
            if (dirOfCol > 0) // player's right, pushes left
            {
                player.x = dimensions.x - player.width / 2.0;
                cout << "player's right collision" << endl;
            }
            else // player's left, pushes right
            {
                player.x = dimensions.x + dimensions.width + player.width / 2.0;
                cout << "player's left collision" << endl;
            }
            player.speed_x = 0;
            player.framesAccelerated = 0;
            player.speed_x_outside = speed_x;
        }
    }
    else
    {
        // cout << "\n\n\n\n\nno collision\n\n\n\n" << endl;
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
