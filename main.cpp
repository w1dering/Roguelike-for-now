#include <iostream>
#include "raylib.h"
#include <tgmath.h>
#include <iostream>
#include <vector>

#include "Player/Player.h"
#include "Obstacles/Platform.h"
#include "Weapons/Bow.h"

using namespace std;

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 600;

    // Player
    Player player;
    player.x = 100;
    player.y = 100;

    // Bow
    Bow bow;

    // Platform
    // move below to platform.cpp class (eventually)
    vector<Platform> platforms;
    Platform ground(0, screenHeight - 50, screenWidth + 50, 50);
    Platform plat1(0, 500, 100, 50);
    Platform plat2(0, 250, 100, 50);
    Platform plat3(0, 400, 100, 50, {Vector3{0.2, 0.1, 10}, Vector3{0, 0, 40}, Vector3{-0.2, -0.1, 20}, Vector3{0, 0, 40}, Vector3{0.2, 0.1, 10}});
    Platform plat4(0, 100, 100, 50, {Vector3{5, 0, 3}, Vector3{0, 0, 54}, Vector3{-0.5, 0, 6}, Vector3{0, 0, 54}, Vector3{0.5, 0, 3}});

    InitWindow(screenWidth, screenHeight, "Roguelike for now");
    SetTargetFPS(60);
    bool thFps = true;

    platforms.push_back(ground);
    platforms.push_back(plat1);
    platforms.push_back(plat2);
    platforms.push_back(plat3);
    platforms.push_back(plat4);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyDown(KEY_TAB))
        {
            if (!thFps)
            {
                SetTargetFPS(30);
                thFps = true;
            }
            else
            {
                SetTargetFPS(1);
                thFps = false;
            }
        }

        // for (int i = 0; i < (int)platforms.size(); i++)
        // {
        //     platforms[i].movePlatform();
        // }

        player.move();
        player.airborne = true;
        player.speed_x_outside = 0;
        player.speed_y_outside = 0;

        for (int i = 0; i < (int)platforms.size(); i++)
        {
            platforms[i].movePlatform();
            platforms[i].collision(player);
            if (player.airborne)
            {
                player.airborne = !(player.y >= platforms[i].dimensions.y - player.height / 2.0 &&
                                    player.y <= platforms[i].dimensions.y + 2 - player.height / 2.0);
            }
            // DrawRectangle(platforms[i].effectiveRectangle.x, platforms[i].effectiveRectangle.y, platforms[i].effectiveRectangle.width, platforms[i].effectiveRectangle.height, YELLOW);

            // if (i == (int) platforms.size() - 1)
            // {
            //     player.prev_x = player.x;
            //     player.prev_y = player.y;
            //     cout << "prev_x TL updated to " << (player.prev_x - player.width / 2.0) << endl;
            //     cout << "prev_y TL updated to " << (player.prev_y - player.height / 2.0) << endl;
            // }

            DrawRectangle(platforms[i].dimensions.x, platforms[i].dimensions.y, platforms[i].dimensions.width, platforms[i].dimensions.height, WHITE); // draw platform
        }

        // doesn't let the ball go out of bounds
        if (player.x >= screenWidth - player.width / 2.0)
            player.x = screenWidth - player.width / 2.0;
        if (player.x <= player.width / 2.0)
            player.x = player.width / 2.0;
        if (player.y >= screenHeight - player.height / 2.0)
            player.y = screenHeight - player.height / 2.0;
        if (player.y <= player.height / 2.0)
            player.y = player.height / 2.0;

        // updates the 3x3 grid of player hitboxes, after collisions have been calculated and adjustments made
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                player.hitbox[r][c].x = player.x + (player.width / 2.0) * (c - 1);
                player.hitbox[r][c].y = player.y + (player.height / 2.0) * (r - 1);
            }
        }

        if (player.showDashShadows == true)
        {
            if (player.dashingFrames % 3 == 0 && player.dashingFrames != -1)
            {
                player.dashTrail[0].z = 180;
            }

            for (int i = 0; i < (int)player.dashTrail.size(); i++)
            {
                if (player.dashTrail[i].z > 0)
                {
                    Color shadowColor{102, 191, 255, (unsigned char)player.dashTrail[i].z};
                    DrawCircle(player.dashTrail[i].x, player.dashTrail[i].y, player.width / 2.0, shadowColor);
                    player.dashTrail[i].z -= 5;
                }

                if (player.dashTrail[i].z <= 0)
                {
                    vector<Vector3>::iterator it = player.dashTrail.begin();
                    advance(it, i);
                    player.dashTrail.erase(it);
                    if (player.dashTrail.size() == 0)
                    {
                        player.showDashShadows = false;
                    }
                }
            }
        }

        // Bow primary fire
        if (bow.travelDistance == 0) // ensures there isn't already an arrow when trying to fire
        {
            if (IsMouseButtonDown(0))
            { // primary fire charging
                bow.charge(player.x, player.y, GetMousePosition());
                DrawLineEx(Vector2{player.x, player.y}, bow.indicator, 10, Fade(WHITE, bow.chargeFrames / 60));
            }
            else if (IsMouseButtonReleased(0))
            { // primary fire released
                bow.arrow.x = player.x;
                bow.arrow.y = player.y;
                bow.aimPositionX = (int)GetMousePosition().x;
                bow.aimPositionY = (int)GetMousePosition().y;
                bow.playerPositionX = player.x;
                bow.playerPositionY = player.y;
                bow.travelDistance = 30;
                bow.chargePower = bow.chargeFrames;
                bow.chargeFrames = 0;
            }
        }
        if (bow.travelDistance > 0)
        { // arrow go nyoooooooooooooom
            bow.fire(bow.playerPositionX, bow.playerPositionY, bow.aimAngle);
            bow.travelDistance--;
            DrawCircle(bow.arrow.x, bow.arrow.y, 10, WHITE);
        }

        if (player.dashes > 0)
        {
            DrawCircle(player.x, player.y, player.width / 2.0, SKYBLUE); // sky blue ring around player to indicate they have a dash
            DrawCircle(player.x, player.y, player.width / 2.0 * 0.6, player.playerColor);
        }
        else
        {
            DrawCircle(player.x, player.y, player.width / 2.0, player.playerColor);
        }

        // rendering hp
        // DrawRectangle(10, 10, (screenWidth / 2.0) - 20, 80, BLACK);
        DrawRectangle(20, 20, (player.hp / player.maxHp * screenWidth / 2.0) - 40, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}