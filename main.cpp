#include <iostream>
#include <raylib.h>
#include <tgmath.h>
#include <ctime>
#include <iostream>
#include <vector>

#include <Platform.cpp>
#include <Weapons\Bow.cpp>

using namespace std;

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 600;

    // Player player
    // move below to player.cpp class
    Player player;
    player.x = 50;
    player.y = 530;

    // Bow
    Bow bow;

    // Platform platform1
    // move below to platform.cpp class (eventually)
    vector<Platform> platforms;
    Platform ground(0, screenHeight - 50, screenWidth + 50, 50);
    Platform plat1(0, 100, 100, 50);
    Platform plat2(0, 250, 100, 50);
    Platform plat3(0, 400, 100, 50);
    Platform plat4(0, 500, 100, 50);

    InitWindow(screenWidth, screenHeight, "Roguelike for now");
    SetTargetFPS(60);

    platforms.push_back(ground);
    platforms.push_back(plat1);
    platforms.push_back(plat2);
    platforms.push_back(plat3);
    platforms.push_back(plat4);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        player.airborne = true;
        for (int i = 0; i < (int)platforms.size(); i++)
        {
            platforms[i].collision(player);
            DrawRectangle(platforms[i].platform.x, platforms[i].platform.y, platforms[i].platform.width, platforms[i].platform.height, WHITE); // draw platform
        }

        player.move(player.x, player.y);

        // doesn't let the ball go out of bounds
        if (player.x >= screenWidth - player.width / 2.0)
            player.x = screenWidth - player.width / 2.0;
        if (player.x <= player.width / 2.0)
            player.x = player.width / 2.0;
        if (player.y >= screenHeight - player.height / 2.0)
            player.y = screenHeight - player.height / 2.0;
        if (player.y <= player.height / 2.0)
            player.y = player.height / 2.0;

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
        if (IsMouseButtonDown(0)) { // primary fire charging
            bow.charge(player.x, player.y, GetMousePosition());
            Vector2 tempPlayerPos{player.x, player.y};
            DrawLineEx(tempPlayerPos, bow.indicator, 10, Fade(WHITE, bow.chargePower/90));
        }
        if (IsMouseButtonReleased(0) && bow.chargePower>=30) { // primary fire released
            bow.chargePower = 0;
            
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

        if (player.airborne)
        {
            DrawCircle(600, 400, 15, RED);
        }

        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                DrawCircle(player.hitbox[r][c].x, player.hitbox[r][c].y, 5, RED);
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}