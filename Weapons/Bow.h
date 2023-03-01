#ifndef _BOW_
#define _BOW_

#include <raylib.h>
#include <math.h>

class Bow
{
public:
    Vector2 indicator;
    int indicatorLength = 50;
    float chargeFrames = 0;
    float chargePower = 0;
    double aimAngle = 0;
    int aimPositionX = 0;
    int aimPositionY = 0;
    Vector2 arrow;
    int travelDistance = 30;

    void charge(float playerx, float playery, Vector2 mousePos);
    void fire(float playerx, float playery, double theta);
};
#endif