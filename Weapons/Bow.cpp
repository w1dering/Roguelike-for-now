#include <iostream>

#include "Bow.h"

using namespace std;

void Bow::charge(float playerx, float playery, Vector2 mousePos)
{
    // angle addition
    aimAngle = atan((double)(mousePos.y - playery) / (mousePos.x - playerx));
    if ((mousePos.y >= playery && mousePos.x >= playerx) || (mousePos.y <= playery && mousePos.x >= playerx))
    {
        indicator.y = (indicatorLength * sin(aimAngle)) + playery;
        indicator.x = (indicatorLength * cos(aimAngle)) + playerx;
    }
    else
    {
        indicator.y = -(indicatorLength * sin(aimAngle)) + playery;
        indicator.x = -(indicatorLength * cos(aimAngle)) + playerx;
    }
    if (chargeFrames < 60)
    {
        chargeFrames++;
    }
}

void Bow::fire(float playerx, float playery, double theta)
{
    if ((aimPositionY >= playery && aimPositionX >= playerx) || (aimPositionY <= playery && aimPositionX >= playerx))
    {
        arrow.y += (chargePower)*sin(theta) / 2;
        arrow.x += (chargePower)*cos(theta) / 2;
    }
    else
    {
        arrow.y -= (chargePower)*sin(theta) / 2;
        arrow.x -= (chargePower)*cos(theta) / 2;
    }
}