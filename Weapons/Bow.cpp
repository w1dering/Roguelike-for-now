
class Bow
{
public:
    Vector2 indicator;
    int indicatorLength = 50;
    float chargePower = 0;
    double aimAngle;

    void charge(float playerx, float playery, Vector2 mousePos)
    {
        // angle addition
        aimAngle = atan((double)(mousePos.y - playery) / (mousePos.x - playerx));
        if ((mousePos.y >= playery && mousePos.x >= playerx) || (mousePos.y <= playery && mousePos.x >= playerx))
        {
            indicator.y = (indicatorLength * sin(aimAngle)) + playery;
            indicator.x = (indicatorLength * cos(aimAngle)) + playerx;
        } else {
            indicator.y = -(indicatorLength * sin(aimAngle)) + playery;
            indicator.x = -(indicatorLength * cos(aimAngle)) + playerx;
        }
        chargePower++;
    }

    void fire() {
        
    }
};