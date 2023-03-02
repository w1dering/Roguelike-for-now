/*
#include <raylib.h>
#include <iostream>

#include "Platform.h"

void Platform::collision(Player &player)
{
    if (CheckCollisionRecs(Rectangle{player.x - (player.width / (float)2.0), player.y - (player.height / (float)2.0), player.width, player.height},
                           Rectangle{dimensions.x, dimensions.y, dimensions.width, dimensions.height})) // checks if boxes are colliding
    {
        float min = abs(player.y + player.height / 2.0 - dimensions.y);
        cout << "dist bot = " << min << endl;
        
        int minDir = 0; // 0 is player's bottom, 1 is left, 2 is top, 3 is right

        float left = abs(player.x - player.width / 2.0 - (dimensions.x + dimensions.width));
        cout << "dist left = -------------------------------------------" << left << endl;
        if (left < min)
        {
            min = left;
            minDir = 1;
        }

        float up = abs(player.y - player.height / 2.0 - (dimensions.y + dimensions.height));
        cout << "dist up = " << up << endl; 
        if (up < min)
        {
            min = up;
            minDir = 2;
        }

        float right = abs(player.x + player.width / 2.0 - dimensions.x);
        cout << "dist right = -----------------------------------------" << right << endl;
        if (right < min)
        {
            min = right;
            minDir = 3;
        }


        switch (minDir)
        {
        case 2: // player's top
            player.y = dimensions.y + dimensions.height + player.height / 2.0;
            player.speed_y = 0;
            player.jumpingFrames = 0;
            cout << "pl top" << endl;
            break;
        case 1: // player's left
            player.x = dimensions.x - player.width / 2.0;
            player.speed_x = 0;
            player.framesAccelerated = 0;
            player.speed_x_outside = speed_x;
                        cout << "pl left" << endl;
            break;
        case 0: // player's bottom
            player.y = dimensions.y + 3.0 - player.height / 2.0;
            player.framesFalling = 0;
            player.speed_y = speed_y - 3.0;
            player.airborne = false;
            player.dashes = player.maxDashes;
            player.speed_x_outside = speed_x;
            player.speed_y_outside = speed_y;
            player.jumpingFrames = 0;
                        cout << "pl bot" << endl;

            break;
        case 3: // player's right
            player.x = dimensions.x + dimensions.width + player.width / 2.0;
            player.speed_x = 0;
            player.framesAccelerated = 0;
            player.speed_x_outside = speed_x;
                        cout << "pl right" << endl;

            break;
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
*/