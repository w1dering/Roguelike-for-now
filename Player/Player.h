#ifndef _PLAYER_
#define _PLAYER_

#include <raylib.h>
#include <tgmath.h>
#include <vector>
#include <iostream>

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
    std::vector<Vector3> dashTrail;
    bool showDashShadows = false;

    // player hitbox vectors
    Vector2 hitbox[3][3];

    // player weaponry
    int swordSwingFrames = 0;

    Player() {}

    void move(float &x, float &y);
};
#endif