/*
#include <raylib.h>
#include <iostream>

#include "Platform.h"

void Platform::collision(Player &player)
{
    Vector2 prevPos{player.x - player.speed_x, player.y - -player.speed_y};
    Vector2 prevPosEffRec{speed_x > 0 ? (dimensions.x - speed_x) : dimensions.x, speed_y < 0 ? (dimensions.y + speed_y) : (dimensions.y + 2 * speed_y)};

    // debugging (will likely need later on)
    cout << "\n\nprevPos: " << prevPos.x << ", " << prevPos.y << ", " << player.width << ", " << player.height << endl;
    cout << "prevPos top left: " << prevPos.x - player.width / (float)2.0 << ", " << player.y - player.height / (float)2.0 << endl;
    cout << "\nplayer: " << player.x << ", " << player.y << ", speeds: " << player.speed_x << ", " << player.speed_y << endl;
    cout << "player top left: " << player.x - player.width / (float)2.0 << ", " << player.y - player.height / (float)2.0 << endl;
    cout << "platform: " << dimensions.x << ", " << dimensions.y << ", " << dimensions.width << ", " << dimensions.height << endl;
    cout << "platform speed: " << speed_x << ", " << speed_y << endl;

    float prevPosTLX = prevPos.x - player.width / (float)2.0;
    float prevPosTLY = prevPos.y - player.height / (float)2.0;
    float playerTLX = player.x - player.width / (float)2.0;
    float playerTLY = player.y - player.height / (float)2.0;

    effectiveRectangle = {speed_x > 0 ? dimensions.x : (dimensions.x + speed_x), speed_y < 0 ? dimensions.y : (dimensions.y + speed_y), dimensions.width + speed_x, dimensions.height + speed_y};
    cout << "effPlatform: " << effectiveRectangle.x << ", " << effectiveRectangle.y << ", " << effectiveRectangle.width << ", " << effectiveRectangle.height << endl;

    cout << "prevEffRec: " << prevPosEffRec.x << ", " << prevPosEffRec.y << endl;

    cout << "check with prev x, post y: " << CheckCollisionRecs(Rectangle{prevPosTLX, playerTLY, player.width, player.height}, effectiveRectangle) << endl;
    cout << "check with prev x, prev y: " << CheckCollisionRecs(Rectangle{prevPosTLX, prevPosTLY, player.width, player.height}, effectiveRectangle) << endl;
    cout << "check rec with prev x, post y: " << CheckCollisionRecs(Rectangle{playerTLX, playerTLY, player.width, player.height}, // only change y of rec collides
                            Rectangle{prevPosEffRec.x, effectiveRectangle.y, effectiveRectangle.width, effectiveRectangle.height}) << endl;;
    cout << "check rec with prev x, prev y: " << CheckCollisionRecs(Rectangle{playerTLX, playerTLY, player.width, player.height},                                         // no change, no collide
                                 Rectangle{prevPosEffRec.x, prevPosEffRec.y, effectiveRectangle.width, effectiveRectangle.height}) << endl;                        

    if (((CheckCollisionRecs(Rectangle{prevPosTLX, playerTLY, player.width, player.height}, // only change y collides
                             effectiveRectangle) &&
          !CheckCollisionRecs(Rectangle{prevPosTLX, prevPosTLY, player.width, player.height}, // no change does not collide
                              effectiveRectangle)) ||
         (CheckCollisionRecs(Rectangle{playerTLX, playerTLY, player.width, player.height}, // only change y of rec collides
                            Rectangle{prevPosEffRec.x, effectiveRectangle.y, effectiveRectangle.width, effectiveRectangle.height}) &&
             !CheckCollisionRecs(Rectangle{playerTLX, playerTLY, player.width, player.height},                                         // no change, no collide
                                 Rectangle{prevPosEffRec.x, prevPosEffRec.y, effectiveRectangle.width, effectiveRectangle.height}))) || // normal case
        // special case
        (!CheckCollisionRecs(Rectangle{prevPosTLX, prevPosTLY, player.width, player.height},
                             effectiveRectangle) && // previous position is not colliding
         !CheckCollisionRecs(Rectangle{playerTLX, prevPosTLY, player.width, player.height},
                             effectiveRectangle) && // if prev position continued x dir, would not collide
         !CheckCollisionRecs(Rectangle{prevPosTLX, playerTLY, player.width, player.height},
                             effectiveRectangle) && // if prev position continued y dir, would not collide
         CheckCollisionRecs(Rectangle{playerTLX, playerTLY, player.width, player.height},
                            effectiveRectangle)))
    {
        // player bottom, platform top checker
        if (player.y > prevPos.y || effectiveRectangle.y < prevPosEffRec.y)
        {
            player.y = dimensions.y - player.height / 2.0;
            player.framesFalling = 0;
            player.speed_y = speed_y - 2.0; // to ensure collision still occurs, as the player needs to be moving to check
            // if (player.speed_y <= 0 && player.speed_y >= -0.001)
            // {
            //     player.speed_y = 0;
            // }
            player.jumpingFrames = 0;
            player.airborne = false;
            player.dashes = player.maxDashes;
            player.speed_x_outside = speed_x;
            player.speed_y_outside = speed_y;
            cout << "player bottom collide with speed_x = " << speed_x << endl;
        }
        // player top, platform bottom checker
        else
        {
            player.y = dimensions.y + dimensions.height + player.height / 2.0;
            player.speed_y = 0;
            player.jumpingFrames = 0;
            cout << "player top collide" << endl;
        }
    }
    else if (CheckCollisionRecs(Rectangle{playerTLX, prevPosTLY, player.width, player.height},
                                effectiveRectangle) !=
             CheckCollisionRecs(Rectangle{prevPosTLX, prevPosTLY, player.width, player.height},
                                effectiveRectangle))
    {
        // player right, platform left checker
        if (player.x > prevPos.x)
        {
            player.x = dimensions.x - player.width / 2.0;
            cout << "player right collide" << endl;
        }
        // player left, platform right checker
        else
        {
            player.x = dimensions.x + dimensions.width + player.width / 2.0;
            cout << "player left collide" << endl;
        }
        player.speed_x = 0;
        player.framesAccelerated = 0;
        player.speed_x_outside = speed_x;
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